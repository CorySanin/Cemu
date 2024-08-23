#include "XapfishDiscordPresence.h"

#ifdef ENABLE_DISCORD_RPC

#include <discord_rpc.h>
#include <boost/algorithm/string.hpp>
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
		if (icon_string == "0005000010176900" || icon_string == "0005000010176a00")
		{
			uint8* map = memory_getPointerFromVirtualOffset(0x120e1ec8);
			std::string mapstr(reinterpret_cast<char*>(map));
			if (map && !mapstr.empty())
			{
				icon_string = mapstr;
				if (mapstr == "Fld_Plaza00_Plz")
				{
					details_string = "In plaza";
				}
				else if (mapstr == "Fld_ShootingRange_Shr")
				{
					details_string = "Shooting Range";
				}
				else if (MapStrMatch(mapstr, "Fld_Crank00"))
				{
					icon_string = "Fld_Crank00";
					details_string = "Urchin Underpass";
				}
				else if (MapStrMatch(mapstr, "Fld_Warehouse00"))
				{
					icon_string = "Fld_Warehouse00";
					details_string = "Walleye Warehouse";
				}
				else if (MapStrMatch(mapstr, "Fld_SeaPlant00"))
				{
					icon_string = "Fld_SeaPlant00";
					details_string = "Saltspray Rig";
				}
				else if (MapStrMatch(mapstr, "Fld_UpDown00"))
				{
					icon_string = "Fld_UpDown00";
					details_string = "Arowana Mall";
				}
				else if (MapStrMatch(mapstr, "Fld_SkatePark00"))
				{
					icon_string = "Fld_SkatePark00";
					details_string = "Blackbelly Skatepark";
				}
				else if (MapStrMatch(mapstr, "Fld_Athletic00"))
				{
					icon_string = "Fld_Athletic00";
					details_string = "Camp Triggerfish";
				}
				else if (MapStrMatch(mapstr, "Fld_Amida00"))
				{
					icon_string = "Fld_Amida00";
					details_string = "Port Mackerel";
				}
				else if (MapStrMatch(mapstr, "Fld_Maze00"))
				{
					icon_string = "Fld_Maze00";
					details_string = "Kelp Dome";
				}
				else if (MapStrMatch(mapstr, "Fld_Tuzura00"))
				{
					icon_string = "Fld_Tuzura00";
					details_string = "Moray Towers";
				}
				else if (MapStrMatch(mapstr, "Fld_Ruins00"))
				{
					icon_string = "Fld_Ruins00";
					details_string = "Bluefin Depot";
				}
				else if (MapStrMatch(mapstr, "Fld_Office00"))
				{
					icon_string = "Fld_Office00";
					details_string = "Ancho-V Games";
				}
				else if (MapStrMatch(mapstr, "Fld_Quarry00"))
				{
					icon_string = "Fld_Quarry00";
					details_string = "Piranha Pit";
				}
				else if (MapStrMatch(mapstr, "Fld_Jyoheki00"))
				{
					icon_string = "Fld_Jyoheki00";
					details_string = "Flounder Heights";
				}
				else if (MapStrMatch(mapstr, "Fld_Pivot00"))
				{
					icon_string = "Fld_Pivot00";
					details_string = "Museum d'Alfonsino";
				}
				else if (MapStrMatch(mapstr, "Fld_Hiagari00"))
				{
					icon_string = "Fld_Hiagari00";
					details_string = "Mahi-Mahi Resort";
				}
				else if (MapStrMatch(mapstr, "Fld_Kaisou00"))
				{
					icon_string = "Fld_Kaisou00";
					details_string = "Hammerhead Bridge";
				}
				else if (mapstr == "Fld_Tutorial00_Ttr")
				{
					icon_string = "Fld_Tutorial00_Ttr";
					details_string = "Tutorial Island";
				}
			}
		}
		break;
	default:
		assert(false);
		break;
	}
	boost::algorithm::to_lower(icon_string);
	discord_presence.details = details_string.c_str();
	discord_presence.state = state_string.c_str();
	// discord_presence.startTimestamp = time(nullptr);
	discord_presence.largeImageText = BUILD_VERSION_WITH_NAME_STRING;
	discord_presence.largeImageKey = icon_string.c_str();
	Discord_UpdatePresence(&discord_presence);
}

bool DiscordPresence::MapStrMatch(const std::string& map, const std::string& check) const
{
	return (map == check + "_Vss") || (map == check + "_Dul");
}

void DiscordPresence::ClearPresence() const
{
	Discord_ClearPresence();
}

#endif