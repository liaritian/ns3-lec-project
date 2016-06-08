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

#include <iostream>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("HelloSimulator");
//word1表示姓名，word2表示我的学号，nn表示输出频率（即每隔ns一个输出)
static void printHello(std::string word1,std::string word2,double n) {
	std::cout<<Simulator::Now()<<" Hello "<<word1<<word2<<std::endl;
	Simulator::Schedule(Seconds(n),&printHello,word1,word2,n);
}

int
main (int argc, char *argv[])
{
	CommandLine cmd;
	std::string name,number;
        double freq;
	cmd.AddValue ("name", "my name", name);
        cmd.AddValue ("number", "my number", number);
        cmd.AddValue ("nn", "my number", freq);
	cmd.Parse(argc,argv);

	printHello(name,number,freq);
	//std::cout<<"hello commit"<<std::endl;

	Simulator::Stop(Seconds(5));
	Simulator::Run ();
	Simulator::Destroy ();
}
