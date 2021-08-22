#pragma once

typedef struct PlayerStats {
	COORD pos;
	size_t health;
	char playerIcon;
	DWORD foregroundColor;
	DWORD backgroundColor;
}playerStats;

playerStats InitPlayer();
int UpdatePlayerPos(playerStats* ps);
int DisplayPlayer(playerStats* ps);
