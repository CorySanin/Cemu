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
};

#endif
