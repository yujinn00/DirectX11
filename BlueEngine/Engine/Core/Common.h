#pragma once

#define WIN_LEAN_AND_MEAN
#define NOMINMAX

#include <Windows.h>
#include <comdef.h>

// ���� �޼��� ��� ��ũ�� �Լ�.
#define ShowErrorMessage(message, reason)				\
wchar_t buffer[256] = {};								\
swprintf_s(buffer, 256, TEXT("[File: %s]\n[Line: %d]\n[Function: %s]\n[Message: %s]\n[Reason: %s]"),	\
TEXT(__FILE__), __LINE__, TEXT(__FUNCTION__), message, reason);	\
MessageBox(nullptr, buffer, TEXT("Error"), MB_OK);

// D3D ȣ�� ���� Ȯ�� ��ũ�� �Լ�.
#define ThrowIfFailed(result, message)					\
if (FAILED(result))										\
{														\
	_com_error error(result);							\
	ShowErrorMessage(message, error.ErrorMessage());	\
	__debugbreak();										\
}
