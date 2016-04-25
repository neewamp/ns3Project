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
#include <iostream>
#include "ns3/mobility-module.h"
#include "ns3/simple-wireless-tdma-module.h"
#include "ns3/csma-module.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include<string>
using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");


double ExpRnd(double mean)
{
  double unif_rnd,exp_rnd;
  unif_rnd=(double)rand()/(double) RAND_MAX;
  exp_rnd=-mean*log(1-unif_rnd);
  return(exp_rnd);
}



int
main (int argc, char *argv[])
{
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
  
  NodeContainer tdmaNodes;
  tdmaNodes.Create (100);

  
  TdmaHelper tdma = TdmaHelper(tdmaNodes.GetN(), tdmaNodes.GetN() );
  std::string rate;
  std::cin >> rate;
  // rate = "100";
  rate+="Mbps";
  TdmaControllerHelper controller;
  controller.Set ("SlotTime", TimeValue (MicroSeconds (1100)));
  controller.Set ("GaurdTime", TimeValue (MicroSeconds (100)));
  controller.Set ("DataRate", StringValue (rate));//was 100Mbps
  controller.Set ("InterFrameTime", TimeValue (MicroSeconds (10)));
  // ExpRnd(1.0);
  //  controller.Set ("InterFrameTime", TimeValue (NanoSeconds (ExpRnd(1.0))));
  tdma.SetTdmaControllerHelper (controller);

  
  NetDeviceContainer tdmaDevices;
  tdmaDevices = tdma.Install (tdmaNodes);

  
  MobilityHelper mobility; 
  mobility.Install(tdmaNodes);  
  
  InternetStackHelper stack;
  stack.Install (tdmaNodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces = address.Assign (tdmaDevices);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (tdmaNodes);
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (30.0));

  
  double interval = 1.0;
  std::cin >> interval;


  int PacketSize = 1024;
  // std::cin >> PacketSize;
  UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (3));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (interval)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));  
  echoClient.SetAttribute ("PacketSize", UintegerValue (PacketSize));  
  //echoClient.SetAttribute ("PacketSize", UintegerValue (1024));  
  int nodes = 3;
  // std::cin >> nodes;
  for (int i = 0; i < nodes; i++)
    echoClient.Install(tdmaNodes.Get(i));
  //edited line 290 in the simple-wirless-tdma/modules/controller.cc commented out to allow the packet size to increase.  

  Simulator::Stop(Seconds(30));
  // ApplicationContainer clientApps = echoClient.Install (tdmaNodes.Get (0));
  // clientApps.Start (Seconds (2.0));
  // clientApps.Stop (Seconds (30.0));

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
