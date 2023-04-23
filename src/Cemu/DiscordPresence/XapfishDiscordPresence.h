#pragma once

#ifdef ENABLE_DISCORD_RPC

class DiscordPresence
{
public:
	enum State
	{
		Idling,
		Playing,
	};

	DiscordPresence();
	~DiscordPresence();

	void UpdatePresence(State state, const std::string& text = {}, const uint64 titleId = 0) const;
	void ClearPresence() const;
<<<<<<< HEAD
private:
	class DiscordRPCLite* m_rpcClient = nullptr;
	bool MapStrMatch(const std::string& map, const std::string& check) const;
=======
>>>>>>> 0b33211 (new extendable Discord rich presence class)
};

#endif
