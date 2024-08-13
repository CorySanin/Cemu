#include "XapfishDiscordPresence.h"

#ifdef ENABLE_DISCORD_RPC

#include "DiscordRPCLite.h"

DiscordPresence::DiscordPresence()
{
	m_rpcClient = new DiscordRPCLite("1098390888738201673");
	UpdatePresence(Idling);
}

DiscordPresence::~DiscordPresence()
{
	ClearPresence();
	if (m_rpcClient)
		delete m_rpcClient;
}

void DiscordPresence::UpdatePresence(State state, const std::string& text, const uint64 titleId) const
{
	if (!m_rpcClient)
		return;
	DiscordLiteRichPresence discordPresence{};

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
				else if (mapstr == "Fld_World00_Wld")
				{
					details_string = "Octo Valley";
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
				else
				{
					icon_string = "sp_mission";
					details_string = "Octo Valley Mission";
				}
			}
		}
		break;
	default:
		assert(false);
		break;
	}

	discordPresence.details = details_string;
	discordPresence.state = state_string;
	// discordPresence.startTimestamp = time(nullptr);
	discordPresence.largeImageText = BUILD_VERSION_WITH_NAME_STRING;
	discordPresence.largeImageKey = icon_string;
	m_rpcClient->UpdateRichPresence(discordPresence);
}

bool DiscordPresence::MapStrMatch(const std::string& map, const std::string& check) const
{
	return (map == check + "_Vss") || (map == check + "_Dul");
}

bool DiscordPresence::MapStrMatch(const std::string& map, const std::string& check) const
{
	return (map == check + "_Vss") || (map == check + "_Dul");
}

void DiscordPresence::ClearPresence() const
{
	if (!m_rpcClient)
		return;
	m_rpcClient->ClearRichPresence();
}

#endif