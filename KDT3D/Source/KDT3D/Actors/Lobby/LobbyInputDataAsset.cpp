// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Lobby/LobbyInputDataAsset.h"

bool ULobbyInputDataAsset::CheckValid()
{
	check(IMC_Default);
	check(MoveAction);
	check(LookMouseAction);

	return true;
}
