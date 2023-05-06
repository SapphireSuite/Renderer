// Copyright (c) 2023 Sapphire's Suite. All Rights Reserved.

#include <SA/Collections/Debug>

void Init()
{
	SA::Debug::InitDefaultLogger();
}

void Uninit()
{
}

int main()
{
	Init();



	Uninit();

	return 0;
}
