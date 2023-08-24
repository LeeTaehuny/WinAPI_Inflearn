#pragma once

// 싱글톤을 만드는 코드를 define으로 일반화해줍니다.
#define DECLARE_SINGLE(classname)			\
	private:								\
		classname() { }						\
	public:									\
		static classname* GetInstance()		\
		{									\
			static classname s_instance;	\
											\
			return &s_instance;				\
		}									
					
// 싱글톤을 사용하는 입장에서도 사용하기 편리하게 일반화해줍니다.
#define GET_SINGLE(classname) classname::GetInstance()

// 동적 할당된 객체를 삭제할 때 편리하게 하기 위해 매크로를 선언합니다.
#define SAFE_DELETE(ptr)					\
	if (ptr)								\
	{										\
		delete ptr;							\
		ptr = nullptr;						\
	}										\