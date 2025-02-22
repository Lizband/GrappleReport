// Copyright 2014-2019 Vladimir Alyamkin. All Rights Reserved.

#include "VaRestLibrary.h"

#include "VaRest.h"
#include "VaRestDefines.h"
#include "VaRestJsonObject.h"
#include "VaRestRequestJSON.h"
#include "VaRestSettings.h"

#include "Misc/Base64.h"

UVaRestSettings* UVaRestLibrary::GetVaRestSettings()
{
	return FVaRestModule::Get().GetSettings();
}

FString UVaRestLibrary::PercentEncode(const FString& Source)
{
	return FGenericPlatformHttp::UrlEncode(Source);
}

FString UVaRestLibrary::Base64Encode(const FString& Source)
{
	TArray<uint8> ByteArray;
	FTCHARToUTF8 StringSrc = FTCHARToUTF8(Source.GetCharArray().GetData());
	ByteArray.Append((uint8*)StringSrc.Get(), StringSrc.Length());

	return FBase64::Encode(ByteArray);
}

bool UVaRestLibrary::Base64Decode(const FString& Source, FString& Dest)
{
	TArray<uint8> ByteArray;
	bool Success = FBase64::Decode(Source, ByteArray);

	FUTF8ToTCHAR StringSrc = FUTF8ToTCHAR((const ANSICHAR*)ByteArray.GetData(), ByteArray.Num());
	Dest.AppendChars(StringSrc.Get(), StringSrc.Length() + 1);

	return Success;
}

bool UVaRestLibrary::Base64EncodeData(const TArray<uint8>& Data, FString& Dest)
{
	if (Data.Num() > 0)
	{
		Dest = FBase64::Encode(Data);
		return true;
	}

	return false;
}

bool UVaRestLibrary::Base64DecodeData(const FString& Source, TArray<uint8>& Dest)
{
	return FBase64::Decode(Source, Dest);
}

FString UVaRestLibrary::StringToMd5(const FString& StringToHash)
{
	return FMD5::HashAnsiString(*StringToHash);
}

FString UVaRestLibrary::StringToSha1(const FString& StringToHash)
{
	FSHA1 Sha1Gen;

	Sha1Gen.Update((unsigned char*)TCHAR_TO_ANSI(*StringToHash), FCString::Strlen(*StringToHash));
	Sha1Gen.Final();

	FString Sha1String;
	for (int32 i = 0; i < 20; i++)
	{
		Sha1String += FString::Printf(TEXT("%02x"), Sha1Gen.m_digest[i]);
	}

	return Sha1String;
}
