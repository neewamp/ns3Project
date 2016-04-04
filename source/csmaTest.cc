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

#include "ns3/socket-factory.h"
#include "ns3/udp-socket-factory.h"
#include "ns3/on-off-helper.h"
#include "ns3/nstime.h"
#include "ns3/csma-module.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
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

  
  
  NodeContainer csmaNodes;
  csmaNodes.Create (3);

  
  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (ExpRnd(1.0))));

  NetDeviceContainer csmaDevices;
  csmaDevices = csma.Install (csmaNodes);
  


  
  InternetStackHelper stack;
  stack.Install (csmaNodes);

  //stack.Install (p2pNodes);
  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces = address.Assign (csmaDevices);

  UdpEchoServerHelper echoServer (9);

  
      
  ApplicationContainer serverApps = echoServer.Install (csmaNodes.Get (1)); 
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (30.0));
  
  

  UdpEchoClientHelper echoClient(interfaces.GetAddress (1),9);//Ipv4Address ("10.1.1.0")/*This workiedinterfaces.GetAddress (3)*/, 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (3));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (ExpRnd(1.0))));// TimeValue (Seconds (10.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));


  
  // for(int i = 0; i < 4 ; i++)
  //   echoClient.Install(csmaNodes.Get(i));
  
  
  
  ApplicationContainer app = echoClient.Install (csmaNodes.Get(4));
  app.Start (Seconds (2.0));
  app.Stop(Seconds (30.0));
  
  
 
  ApplicationContainer app1 = echoClient.Install (csmaNodes.Get(2));
  app1.Start (Seconds (2.0));
  app1.Stop(Seconds (30.0));

  
  // ApplicationContainer apps = echoClient.Install (csmaNodes.Get(3));
  // apps.Start (Seconds (2.0));
  // apps.Stop(Seconds (30.0));
  
  ApplicationContainer clientApps = echoClient.Install (csmaNodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (30.0));


  // Print per flow statistics

  
  Ptr<FlowMonitor> flowMonitor;
  FlowMonitorHelper flowHelper;
  flowMonitor = flowHelper.InstallAll();
  
  Simulator::Stop(Seconds(30));//Seconds(stop_time));
  


  Simulator::Run ();
  flowMonitor->SerializeToXmlFile("NameOfFile.xml", false, false);
  Simulator::Destroy ();
  return 0;
}
