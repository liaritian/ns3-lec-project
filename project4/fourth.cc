/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/propagation-delay-model.h"
#include "ns3/bridge-helper.h"
#include <vector>
#include <stdint.h>
#include <sstream>
#include <fstream>



using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("ThirdScriptExample");		//定义记录组件

int
main (int argc, char *argv[])
{
  bool verbose = true;			//csma节点数量
  uint32_t nWifi = 6;				//wifi节点数量
  uint32_t nAP = 2;
  bool tracing = true;


  CommandLine cmd;
  cmd.AddValue ("nWifi", "Number of wifi STA devices", nWifi);
  cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);
  cmd.AddValue ("tracing", "Enable pcap tracing", tracing);
  cmd.Parse (argc,argv);

  if (nWifi > 250 )
    {
      std::cout << "Too many wifi or csma nodes, no more than 250 each." << std::endl;
      return 1;
    }

  if (verbose)
    {
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);	//启动记录组件
    }

//声明容器
std::vector<NodeContainer> staNodes;
std::vector<NetDeviceContainer> staDevices;
std::vector<NetDeviceContainer> apDevices;
std::vector<Ipv4InterfaceContainer> staInterfaces;
std::vector<Ipv4InterfaceContainer> apInterfaces;
std::vector<YansWifiPhyHelper> phys;
std::vector<WifiHelper> wifis;
std::vector<BridgeHelper> bridges;

NodeContainer wifiApNode;
NetDeviceContainer wifiApNodeDevice;

CsmaHelper csma;
InternetStackHelper stack;
wifiApNode.Create(nAP);
stack.Install(wifiApNode);
wifiApNodeDevice = csma.Install(wifiApNode);

Ipv4AddressHelper address;
//P2P信道
//wifi信道
address.SetBase ("10.1.1.0", "255.255.255.0");

//创建wifista无线终端，AP接入点
for (uint i = 0;i < nAP; ++i)
{
    NodeContainer wifiStaNodes;
    wifiStaNodes.Create (nWifi);

  //创建无线设备于无线节点之间的互联通道，并将通道对象与物理层对象关联
  //确保所有物理层对象使用相同的底层信道，即无线信道
    YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
    channel.SetPropagationDelay("ns3::ConstantSpeedPropagationDelayModel");
    YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();
    phy.SetChannel (channel.Create ());

  //配置速率控制算法，AARF算法
    WifiHelper wifi = WifiHelper::Default ();
    wifi.SetRemoteStationManager ("ns3::AarfWifiManager");

    NqosWifiMacHelper mac = NqosWifiMacHelper::Default ();

  //配置mac类型为sta模式，不发送探测请求
    Ssid ssid = Ssid ("ns-3-ssid");
    mac.SetType ("ns3::StaWifiMac",
               "Ssid", SsidValue (ssid),
               "ActiveProbing", BooleanValue (false));

  //创建无线设备，将mac层和phy层安装到设备上
    NetDeviceContainer staDevice;
    staDevice = wifi.Install (phy, mac, wifiStaNodes);

  //配置AP节点的mac层为AP模式，创建AP设备
    mac.SetType ("ns3::ApWifiMac","Ssid", SsidValue (ssid));
    NetDeviceContainer apDevice;
    apDevice = wifi.Install (phy, mac, wifiApNode.Get(i));
    BridgeHelper bridge;
    NetDeviceContainer bridgeDevices;
    bridgeDevices = bridge.Install (wifiApNode.Get (i), NetDeviceContainer (apDevice, wifiApNodeDevice.Get (i)));

  //配置移动模型，起始位置
    MobilityHelper mobility;

    mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (0.0),
                                 "MinY", DoubleValue (0.0),
                                 "DeltaX", DoubleValue (5.0),
                                 "DeltaY", DoubleValue (5.0),
                                 "GridWidth", UintegerValue (10),
                                 "LayoutType", StringValue ("RowFirst"));

  //配置STA移动方式，RandomWalk2dMobilityModel，随机游走模型
    mobility.SetMobilityModel ("ns3::RandomWalk2dMobilityModel",
                             "Bounds", RectangleValue (Rectangle (0, 500, 0, 500)),
                             "Distance", DoubleValue(30));
    mobility.Install (wifiStaNodes);

//配置AP移动方式，ConstantPositionMobilityModel，固定位置模型
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (wifiApNode.Get(i));

  Ptr<ConstantPositionMobilityModel> mob = wifiApNode.Get(i)->GetObject<ConstantPositionMobilityModel>();
  mob->SetPosition(Vector(225.0 + i*25.0, 250.0, 0.0));

  for (uint n = 0; n < wifiStaNodes.GetN(); n++)
 {
   Ptr<RandomWalk2dMobilityModel> mob = wifiStaNodes.Get(n)->GetObject<RandomWalk2dMobilityModel>();
   switch (n)
   {
   case 0: mob->SetPosition(Vector(216.3 + i*25, 255.0, 0.0));break;
   case 1: mob->SetPosition(Vector(216.3 + i*25, 245.0, 0.0));break;
   case 2: mob->SetPosition(Vector(225.0 + i*25, 240.0, 0.0));break;
   case 3: mob->SetPosition(Vector(233.7 + i*25, 255.0, 0.0));break;
   case 4: mob->SetPosition(Vector(233.7 + i*25, 245.0, 0.0));break;
   case 5: mob->SetPosition(Vector(225.0 + i*25, 260.0, 0.0));break;
   }
 }

  InternetStackHelper stack;
  stack.Install (wifiStaNodes);

  //分配IP地址
  Ipv4InterfaceContainer staInterface;
  Ipv4InterfaceContainer apInterface;
  staInterface = address.Assign (staDevice);
  apInterface = address.Assign (bridgeDevices);

  staNodes.push_back (wifiStaNodes);
  apDevices.push_back (apDevice);
  apInterfaces.push_back (apInterface);
  staDevices.push_back (staDevice);
  staInterfaces.push_back (staInterface);
  phys.push_back (phy);
  wifis.push_back(wifi);
  bridges.push_back(bridge);
}



  //放置echo服务端程序在最右边的csma节点,端口为9
  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (staNodes[0].Get (0));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  //回显客户端放在最后的STA节点，指向CSMA网络的服务器，上面的节点地址，端口为9
  UdpEchoClientHelper echoClient (staInterfaces[0].GetAddress(0), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (20));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (0.1)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (512));

  //安装其他节点应用程序
  ApplicationContainer clientApps =
  echoClient.Install (staNodes[1].Get (4));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));


  //启动互联网络路由
  //Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  Simulator::Stop (Seconds (10.0));

  if (tracing == true)
    {
        AsciiTraceHelper ascii;
      phys[0].EnablePcap ("project4_left", apDevices[0]);
      phys[1].EnablePcap ("project4_right", apDevices[1]);
      csma.EnableAsciiAll(ascii.CreateFileStream ("csma.tr"));
    }

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
