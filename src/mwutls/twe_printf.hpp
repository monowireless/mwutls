/* Copyright (C) 2019-2020 Mono Wireless Inc. All Rights Reserved.
 * Released under MW-OSSLA-1J,1E (MONO WIRELESS OPEN SOURCE SOFTWARE LICENSE AGREEMENT). */

/** @file
 *
 * @defgroup TWESER ヘッダファイル
 *
 * シリアル等の入出力の抽象定義を行う。
 */

#ifndef TWEPRINTF_H_
#define TWEPRINTF_H_

#include "twe_common.hpp"
#include "twe_stream.hpp"

#include "../printf/printf.h"

namespace TWE {
	int fPrintf(TWE::IStreamOut& fp, const char* format, ...);
	int snPrintf(char* buffer, size_t count, const char* format, ...);

	class z_printobj {
	protected:
		const char *_fmt;

		// custom out function
		static inline void _out_fct(char character, void* arg) {
			IStreamOut* pof = static_cast<IStreamOut*>(arg);
			*pof << character;
		}

	public:
		virtual ~z_printobj() = default;
		z_printobj(const char* fmt) : _fmt(fmt) {}
		virtual void do_print(IStreamOut& of) {
			const char_t *p = _fmt;
			while (*p != 0) {
				of << *p;
				++p;
			}
		}
	};

	template <typename T1>
	class z_printobj_1 : public z_printobj {
		T1 _a1;
	public:
		z_printobj_1(const char *fmt, T1 a1) : z_printobj(fmt), _a1(a1) {}
		void do_print(IStreamOut& of) override {	fctprintf(&_out_fct, static_cast<void*>(&of), _fmt, _a1); }
	};

	template <typename T1, typename T2>
	class z_printobj_2 : public z_printobj {
		T1 _a1;
		T2 _a2;
	public:
		z_printobj_2(const char *fmt, T1 a1, T2 a2) : z_printobj(fmt), _a1(a1), _a2(a2) {}
		void do_print(IStreamOut& of) override { fctprintf(&_out_fct, static_cast<void*>(&of), _fmt, _a1, _a2); }
	};

	template <typename T1, typename T2, typename T3>
	class z_printobj_3 : public z_printobj {
		T1 _a1;
		T2 _a2;
		T3 _a3;
	public:
		z_printobj_3(const char *fmt, T1 a1, T2 a2, T3 a3) : z_printobj(fmt), _a1(a1), _a2(a2), _a3(a3) {}
		void do_print(IStreamOut& of) override { fctprintf(&_out_fct, static_cast<void*>(&of), _fmt, _a1, _a2, _a3); }
	};

	template <typename T1, typename T2, typename T3, typename T4>
	class z_printobj_4 : public z_printobj {
		T1 _a1;
		T2 _a2;
		T3 _a3;
		T4 _a4;
	public:
		z_printobj_4(const char *fmt, T1 a1, T2 a2, T3 a3, T4 a4) : z_printobj(fmt), _a1(a1), _a2(a2), _a3(a3), _a4(a4) {}
		void do_print(IStreamOut& of) override { fctprintf(&_out_fct, static_cast<void*>(&of), _fmt, _a1, _a2, _a3, _a4); }
	};

	template <typename T1, typename T2, typename T3, typename T4, typename T5>
	class z_printobj_5 : public z_printobj {
		T1 _a1;
		T2 _a2;
		T3 _a3;
		T4 _a4;
		T5 _a5;
	public:
		z_printobj_5(const char* fmt, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) : z_printobj(fmt), _a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5) {}
		void do_print(IStreamOut& of) override { fctprintf(&_out_fct, static_cast<void*>(&of), _fmt, _a1, _a2, _a3, _a4, _a5); }
	};

	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	class z_printobj_6 : public z_printobj {
		T1 _a1;
		T2 _a2;
		T3 _a3;
		T4 _a4;
		T5 _a5;
		T6 _a6;
	public:
		z_printobj_6(const char* fmt, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) : z_printobj(fmt), _a1(a1), _a2(a2), _a3(a3), _a4(a4), _a5(a5), _a6(a6) {}
		void do_print(IStreamOut& of) override { fctprintf(&_out_fct, static_cast<void*>(&of), _fmt, _a1, _a2, _a3, _a4, _a5, _a6); }
	};

#if 0
	class printfmt {
		std::unique_ptr<_printobj> _pobj;

	public:
		printfmt(const char *fmt) 
			: _pobj(new _printobj(fmt)) {}
		
		template <typename T1>
		printfmt(const char *fmt, T1 a1)
			: _pobj(new _printobj_1<T1>(fmt,a1)) {}

		template <typename T1, typename T2>
		printfmt(const char *fmt, T1 a1, T2 a2)
			: _pobj(new _printobj_2<T1, T2>(fmt,a1,a2)) {}

		template <typename T1, typename T2, typename T3>
		printfmt(const char *fmt, T1 a1, T2 a2, T3 a3)
			: _pobj(new _printobj_3<T1, T2, T3>(fmt,a1,a2,a3)) {}

		template <typename T1, typename T2, typename T3, typename T4>
		printfmt(const char *fmt, T1 a1, T2 a2, T3 a3, T4 a4)
			: _pobj(new _printobj_4<T1, T2, T3, T4>(fmt,a1,a2,a3,a4)) {}

		IStreamOut& operator ()(IStreamOut& of) {
			_pobj->do_print(of);
			return of;
		}
	};
#else

	const size_t MAX_SIZE_PRINTOBJ = sizeof(z_printobj_6<double, double, double, double, double, double>);

	class printfmt {
		uint8_t _pobj[MAX_SIZE_PRINTOBJ];

	public:
		printfmt(const char* fmt) : _pobj() {
			(void)new (static_cast<void*>(_pobj)) z_printobj(fmt);
		}

		template <typename T1>
		printfmt(const char* fmt, T1 a1) : _pobj() {
			static_assert(sizeof(z_printobj_1<T1>(fmt, a1)) <= MAX_SIZE_PRINTOBJ, "Pre-alloc size overflow. Check MAX_SIZE_PRINTOBJ.");
			(void)new (static_cast<void*>(_pobj)) z_printobj_1<T1>(fmt, a1);
		}

		template <typename T1, typename T2>
		printfmt(const char* fmt, T1 a1, T2 a2) : _pobj() {
			static_assert(sizeof(z_printobj_2<T1, T2>) <= MAX_SIZE_PRINTOBJ, "Pre-alloc size overflow. Check MAX_SIZE_PRINTOBJ.");
			(void)new (static_cast<void*>(_pobj)) z_printobj_2<T1, T2>(fmt, a1, a2);
		}

		template <typename T1, typename T2, typename T3>
		printfmt(const char* fmt, T1 a1, T2 a2, T3 a3) : _pobj() {
			static_assert(sizeof(z_printobj_3<T1, T2, T3>) <= MAX_SIZE_PRINTOBJ, "Pre-alloc size overflow. Check MAX_SIZE_PRINTOBJ.");
			(void)new (static_cast<void*>(_pobj)) z_printobj_3<T1, T2, T3>(fmt, a1, a2, a3);
		}

		template <typename T1, typename T2, typename T3, typename T4>
		printfmt(const char* fmt, T1 a1, T2 a2, T3 a3, T4 a4) : _pobj() {
			static_assert(sizeof(z_printobj_4<T1, T2, T3, T4>) <= MAX_SIZE_PRINTOBJ, "Pre-alloc size overflow. Check MAX_SIZE_PRINTOBJ.");
			(void)new (static_cast<void*>(_pobj)) z_printobj_4<T1, T2, T3, T4>(fmt, a1, a2, a3, a4);
		}

		template <typename T1, typename T2, typename T3, typename T4, typename T5>
		printfmt(const char* fmt, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5) : _pobj() {
			static_assert(sizeof(z_printobj_5<T1, T2, T3, T4, T5>) <= MAX_SIZE_PRINTOBJ, "Pre-alloc size overflow. Check MAX_SIZE_PRINTOBJ.");
			(void)new (static_cast<void*>(_pobj)) z_printobj_5<T1, T2, T3, T4, T5>(fmt, a1, a2, a3, a4, a5);
		}

		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		printfmt(const char* fmt, T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6) : _pobj() {
			static_assert(sizeof(z_printobj_6<T1, T2, T3, T4, T5, T6>) <= MAX_SIZE_PRINTOBJ, "Pre-alloc size overflow. Check MAX_SIZE_PRINTOBJ.");
			(void)new (static_cast<void*>(_pobj)) z_printobj_6<T1, T2, T3, T4, T5, T6>(fmt, a1, a2, a3, a4, a5, a6);
		}

		IStreamOut& operator ()(IStreamOut& of) {
			reinterpret_cast<z_printobj*>(_pobj)->do_print(of);
			return of;
		}
	};
	using format = printfmt;
#endif

	inline IStreamOut& operator << (IStreamOut& s, printfmt sc) { return sc(s); } // implement std::endl like object
	inline IStreamOut& operator << (IStreamOut& s, const double d) { return s << printfmt("%.3f", d); }
}

#endif // TWEPRINTF_H_
