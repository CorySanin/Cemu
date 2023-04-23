#include "XapfishDiscordPresence.h"

#ifdef ENABLE_DISCORD_RPC

#include <discord_rpc.h>
#include "Common/version.h"

DiscordPresence::DiscordPresence()
{
	DiscordEventHandlers handlers{};
	Discord_Initialize("1098390888738201673", &handlers, 1, nullptr);
	UpdatePresence(Idling);
}

DiscordPresence::~DiscordPresence()
{
	ClearPresence();
	Discord_Shutdown();
}

void DiscordPresence::UpdatePresence(State state, const std::string& text, const uint64 titleId) const
{
	DiscordRichPresence discord_presence{};

	std::string state_string, details_string, icon_string;
	std::stringstream ss;
	switch (state)
	{
	case Idling:
		details_string = "Idling";
		icon_string = "logo_icon_big_png";
		break;
	case Playing:
		details_string = "Ingame";
		state_string = "Playing " + text;
		ss << std::hex << std::setw(16) << std::setfill('0') << titleId;
		icon_string = ss.str();
		break;
	default:
		assert(false);
		break;
	}

	discord_presence.details = details_string.c_str();
	discord_presence.state = state_string.c_str();
	discord_presence.startTimestamp = time(nullptr);
	discord_presence.largeImageText = BUILD_VERSION_WITH_NAME_STRING;
	discord_presence.largeImageKey = icon_string.c_str();
	Discord_UpdatePresence(&discord_presence);
}

void DiscordPresence::ClearPresence() const
{
	Discord_ClearPresence();
}

#endif