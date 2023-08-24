#pragma once

// 전방 선언
class Object;

// 기존 매니저 클래스 처럼 초기화, 압데이트를 해주는 대신 오브젝트를 들고 있기 위한 클래스입니다.
class ObjectManager
{
	// 해당 클래스를 싱글톤으로 만들어줍니다.
	DECLARE_SINGLE(ObjectManager);

public:
	// 소멸자 함수를 선언합니다.
	~ObjectManager();

	// 오브젝트들을 생성해 반환하는 함수를 정의합니다.
	template<typename T>
	T* CreateObject()
	{
		// 아직 T의 정보가 정해지지도 않았는데 init() 함수를 호출해도 빌드가 성공적으로 완료됩니다.
		// * 자동 추론
		// 만약 Init() 함수를 가지고 있는 GameScene 클래스를 실수로 잘못 넣는 경우에도 성공적으로 완료되므로 주의해야 합니다.

		// 위 상황을 막기 위해 type trait을 해줄 수 있습니다.
		// * 컴파일 타임에 체크해 넣어준 조건(T)이 특정 타입(Object)이 아니라면 로그를 출력해줍니다.
		static_assert(std::is_convertible_v<T*, Object*>);

		// 오브젝트를 생성하고 초기화합니다.
		T* object = new T();
		object->Init();

		return object;
	}

	// 오브젝트를 추가하는 함수를 선언합니다.
	void Add(Object* object);
	// 오브젝트를 삭제하는 함수를 선언합니다.
	void Remove(Object* object);
	// 오브젝트를 전부 삭제하는 함수를 선언합니다.
	void Clear();

	// 외부에서 오브젝트를 사용할 수 있도록 Getter 함수를 정의합니다.
	// * 참조 값(&)을 받아온 이유 : 복사 비용을 아끼기 위함
	const vector<Object*>& GetObjects() { return _objects; }

private:
	// 오브젝트들을 저장할 벡터 컨테이너를 선언합니다.
	vector<Object*> _objects;
};

