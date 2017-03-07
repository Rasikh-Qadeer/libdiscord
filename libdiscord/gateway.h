#pragma once

#include <cstdint>
#include <cpprest/ws_client.h>
#include <thread>

namespace discord
{
  class bot;

  class gateway
  {
    //  Constants
    static const uint8_t LARGE_SERVER;
    static const utility::string_t VERSION;
    static const utility::string_t ENCODING;

    //  Client variables
    utility::string_t m_wss_url;
    web::websockets::client::websocket_callback_client m_client;
    std::mutex m_client_mutex;

    //  Heartbeat variables
    std::thread m_heartbeat_thread;
    uint32_t m_heartbeat_interval;
    bool m_recieved_ack;

    //  Session variables
    uint32_t m_last_seq;
    std::string m_session_id;
    volatile bool m_connected;
    bool m_use_resume;

    //  Owning bot
    std::weak_ptr<bot> m_bot;

    //  Private enumeration for Opcodes
    enum Opcode : uint8_t
    {
      Dispatch = 0,
      Heartbeat,
      Identify,
      Presence,
      Voice_State,
      Voice_Ping,
      Resume,
      Reconnect,
      Request_Members,
      Invalidate_Session,
      Hello,
      Heartbeat_ACK
    };

  public:
    gateway();
  };
}