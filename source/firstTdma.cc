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

#include "ns3/mobility-module.h"
#include "ns3/simple-wireless-tdma-module.h"
#include "ns3/csma-module.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

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
  tdmaNodes.Create (8);

  
  TdmaHelper tdma = TdmaHelper(tdmaNodes.GetN(), tdmaNodes.GetN() );
  // tdma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  //tdma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560));

  
  TdmaControllerHelper controller;
  controller.Set ("SlotTime", TimeValue (MicroSeconds (1100)));
  controller.Set ("GaurdTime", TimeValue (MicroSeconds (100)));

  controller.Set ("InterFrameTime", TimeValue (MicroSeconds (0)));
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

  ApplicationContainer serverApps = echoServer.Install (tdmaNodes.Get (1));
  serverApps.Start (Seconds (2.0));
  serverApps.Stop (Seconds (30.0));

  UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (8));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (ExpRnd(4.0))));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));


  ApplicationContainer app = echoClient.Install (tdmaNodes.Get(5));
  app.Start (Seconds (2.0));
  app.Stop(Seconds (30.0));


  ApplicationContainer app1 = echoClient.Install (tdmaNodes.Get(7));
  app1.Start (Seconds (2.0));
  app1.Stop(Seconds (30.0));


  ApplicationContainer apps = echoClient.Install (tdmaNodes.Get(6));
  apps.Start (Seconds (2.0));
  apps.Stop(Seconds (30.0));
  
  
  ApplicationContainer clientApps = echoClient.Install (tdmaNodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (30.0));

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
