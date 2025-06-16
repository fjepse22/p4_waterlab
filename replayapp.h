#ifndef REPLAY_AND_MODIFY_APP_H
#define REPLAY_AND_MODIFY_APP_H

#include "ns3/application.h"
#include "ns3/address.h"
#include "ns3/ptr.h"
#include "ns3/socket.h"

namespace ns3 {

class ReplayAndModifyApp : public Application
{
public:
  static TypeId GetTypeId (void);
  ReplayAndModifyApp ();
  virtual ~ReplayAndModifyApp ();

protected:
  virtual void StartApplication (void);
  virtual void StopApplication (void);

private:
  void HandleRead (Ptr<Socket> socket);

  Ptr<Socket>     m_socket;
  Address         m_local;
};

} // namespace ns3

#endif // REPLAY_AND_MODIFY_APP_H
