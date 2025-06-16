#include "replayapp.h"
#include "ns3/log.h"
#include "ns3/inet-socket-address.h"
#include "ns3/packet.h"

#include <iostream>
#include <regex>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("replayapp");
NS_OBJECT_ENSURE_REGISTERED (ReplayAndModifyApp);

TypeId replayapp::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::replayapp")
    .SetParent<Application> ()
    .SetGroupName ("Tutorial")
    .AddConstructor<replayapp> ();
  return tid;
}

replayapp::replayapp () {}
replayapp::~replayapp () {}

void
replayapp::StartApplication ()
{
  m_socket = Socket::CreateSocket (GetNode (), TcpSocketFactory::GetTypeId ());
  m_local = InetSocketAddress (Ipv4Address::GetAny (), 9999);
  m_socket->Bind (m_local);
  m_socket->Listen ();
  m_socket->SetRecvCallback (MakeCallback (&replayapp::HandleRead, this));
}

void
replayapp::StopApplication ()
{
  if (m_socket)
    {
      m_socket->Close ();
    }
}

void
replayapp::HandleRead (Ptr<Socket> socket)
{
  Address from;
  Ptr<Socket> clientSocket = socket->Accept ();
  clientSocket->SetRecvCallback ([clientSocket](Ptr<Socket> s) {
    Address clientAddr;
    Ptr<Packet> packet = s->RecvFrom (clientAddr);

    if (packet->GetSize () > 0)
      {
        std::string data;
        data.resize (packet->GetSize ());
        packet->CopyData ((uint8_t *) &data[0], packet->GetSize ());

        NS_LOG_INFO ("Received: " << data);

        // Modify payload
        std::string modified = std::regex_replace (data, std::regex ("temperature=\\d+"), "temperature=0");
        NS_LOG_INFO ("Modified: " << modified);

        Ptr<Packet> response = Create<Packet> ((uint8_t *) modified.c_str (), modified.length ());
        s->Send (response);
      }
  });
}

} // namespace ns3

int main(int argc, char *argv[]) { return 0; }
