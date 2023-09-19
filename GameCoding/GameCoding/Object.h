#pragma once

// 오브젝트의 타입을 구분하기 위한 열거형을 선언합니다.
enum class ObjectType
{
	None,
	Player,		// 플레이어
	Monster,	// 적
	Projectile,	// 발사체
	Env,		// 채집 오브젝트
};

// 게임에 등장하는 오브젝트들 중 최상의 부모 역할을 하는 클래스를 선언합니다.
class Object
{
public:
	// 생성자와 소멸자 함수를 선언합니다.
	// * 계층 구조로 관리하기 위해 소멸자에서 virtual 키워드를 추가합니다.
	Object();
	Object(ObjectType type);
	virtual	~Object();

	// 하위 자식 클래스들에서 구현해야 하는 기본적인 함수들을 정의합니다.
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

public:
	// 자주 사용할 것 같은 Getter, Setter 함수를 정의합니다.
	// * 위치
	void		SetPos(Pos pos) { _pos = pos; }
	Pos			GetPos() { return _pos; }
	// * 오브젝트 타입
	ObjectType	GetObjectType() { return _type; }
	// * 충돌 범위
	float		GetRadius() { return _radius; }
	void		SetRadius(float radius) { _radius = radius; }

protected:
	// 자신의 오브젝트 타입을 저장하기 위한 변수를 선언합니다.
	ObjectType	_type = ObjectType::None;

	// 오브젝트의 스탯을 저장하기 위한 변수를 선언합니다.
	Stat		_stat = {};

	// 모든 오브젝트가 인게임에 배치되는 물체들이라고 가정합니다.
	// * 해당 물체의 위치를 저장하기 위한 변수를 선언합니다.
	Pos			_pos = {};

	// 플레이어와 총알을 모두 원으로 관리할 것이므로 반지름을 저장하기 위한 변수를 선언합니다.
	// * 충돌 범위
	float		_radius = 50.0f;
};

