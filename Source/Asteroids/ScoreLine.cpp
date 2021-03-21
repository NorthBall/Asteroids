// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreLine.h"

/*bool FScoreLine::operator<(const FScoreLine& First,const FScoreLine & Second)
{
	return First.Score<Second.Score;
}

bool FScoreLine::operator==(const FScoreLine & Second)
{
	return Score==Second.Score&&String==Second.String;
}*/
FScoreLine::FScoreLine()
{
	Score = 0;
	String = TEXT("");
}

bool operator<(const FScoreLine & First, const FScoreLine & Second)
{
	return First.Score<Second.Score;
}
