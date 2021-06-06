#pragma once

#ifndef __FUNCTION_H__
#define __FUNCTION_H__

template <typename T>
void Safe_Delete(T& _Dst)
{
	if (_Dst)
	{
		delete _Dst;
		_Dst = nullptr;
	}
}


template <typename T>
bool CompareY(T& _Dst, T& _Src)
{
	return _Dst->Get_Info().vPos.y < _Src->Get_Info().vPos.y;
}

#endif // !__FUNCTION_H__
