#include "pch.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "Sprite.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

TilemapActor::TilemapActor()
{
}

TilemapActor::~TilemapActor()
{
}

void TilemapActor::BeginPlay()
{
	Super::BeginPlay();
}

void TilemapActor::Tick()
{
	Super::Tick();

	TilePicking();
}

void TilemapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	// 만약 타일맵에 대한 정보가 없다면?
	if (_tilemap == nullptr)
	{
		// 종료합니다.
		return;
	}

	// 만약 렌더하지 않겠다고 설정했다면?
	if (_showDebug == false)
	{
		// 종료합니다.
		return;
	}

	// 타일맵의 사이즈 정보를 받아옵니다.
	const Vec2Int mapSize = _tilemap->GetMapSize();
	// 개별 타일의 크기를 받아옵니다.
	const int32 tileSize = _tilemap->GetTileSize();

	// 타일맵의 각각 타일에 대한 정보를 받아옵니다.
	vector<vector<Tile>>& tiles = _tilemap->GetTiles();

	// 테스트를 위해 타일의 정보를 O와 X로만 구분해보도록 하겠습니다.
	// * O 타일의 스프라이트를 받아옵니다.
	Sprite* spriteO = GET_SINGLE(ResourceManager)->GetSprite(L"TileO");
	// * X 타일의 스프라이트를 받아옵니다.
	Sprite* spriteX = GET_SINGLE(ResourceManager)->GetSprite(L"TileX");

	// 카메라의 위치 정보를 받아옵니다.
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	// 컬링 : 화면에 보이는 액터만 화면에 그려주기
	// * 카메라가 찍고 있는 최소 좌표를 구해줍니다.
	int32 leftX = ((int32)cameraPos.x - GWinSizeX / 2);
	int32 leftY = ((int32)cameraPos.y - GWinSizeY / 2);
	int32 rightX = ((int32)cameraPos.x + GWinSizeX / 2);
	int32 rightY = ((int32)cameraPos.y + GWinSizeY / 2);

	// 타일이 몇 번 인덱스에서 시작하는지 계산해줍니다.
	int32 startX = (leftX - _pos.x) / TILE_SIZEX;
	int32 startY = (leftY - _pos.y) / TILE_SIZEY;

	// 타일을 몇 번 인덱스까지 출력해야하는지 계산해줍니다.
	int32 endX = (rightX - _pos.x) / TILE_SIZEX;
	int32 endY = (rightY - _pos.y) / TILE_SIZEY;

	// 맵 크기 정보만큼 반복합니다.
	// * 컬링 적용 (실제 카메라 크기만큼만 렌더링)
	for (int32 y = startY; y <= endY; y++)
	{
		for (int32 x = startX; x <= endX; x++)
		{
			// 예외 처리
			if (x < 0 || x >= mapSize.x || y < 0 || x >= mapSize.y)
			{
				continue;
			}

			// 해당 타일의 값에 따라 분기합니다.
			switch (tiles[y][x].value)
			{
			// 값이 0번인 경우
			case 0:
				// spriteO를 화면에 그려줍니다.
				::TransparentBlt(hdc,
					_pos.x + x * TILE_SIZEX - ((int32)cameraPos.x - GWinSizeX / 2), // 출력될 x 좌표 : 현재 좌표 * x번째 * x 타일 사이즈
					_pos.y + y * TILE_SIZEY - ((int32)cameraPos.y - GWinSizeY / 2), // 출력될 y 좌표 : 현재 좌표 * y번째 * y 타일 사이즈
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetDC(),	// O 그림 출력
					spriteO->GetPos().x,
					spriteO->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteO->GetTransparent()
				);
				break;

			case 1:
				// spriteX를 화면에 그려줍니다.
				::TransparentBlt(hdc,
					_pos.x + x * TILE_SIZEX - ((int32)cameraPos.x - GWinSizeX / 2), // 출력될 x 좌표 : 현재 좌표 * x번째 * x 타일 사이즈
					_pos.y + y * TILE_SIZEY - ((int32)cameraPos.y - GWinSizeY / 2), // 출력될 y 좌표 : 현재 좌표 * y번째 * y 타일 사이즈
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetDC(),	// O 그림 출력
					spriteX->GetPos().x,
					spriteX->GetPos().y,
					TILE_SIZEX,
					TILE_SIZEY,
					spriteX->GetTransparent()
				);
				break;
			}
		}
	}
}

void TilemapActor::TilePicking()
{
	// 만약 마우스 클릭 입력이 들어왔다면?
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		// 카메라 위치 정보를 받아옵니다.
		Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

		// 스크린(화면)상의 x, y 좌표(왼쪽 상단 좌표)를 계산합니다.
		int32 screenX = cameraPos.x - GWinSizeX / 2;
		int32 screenY = cameraPos.y - GWinSizeY / 2;

		// 마우스 위치를 받아옵니다.
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

		// 실제 게임 세상(인게임)에서의 좌표를 구해줍니다.
		int32 posX = mousePos.x + screenX;
		int32 posY = mousePos.y + screenY;

		// 위에서 구한 인게임 좌표 상의 타일 인덱스 번호를 구해줍니다.
		int32 x = posX / TILE_SIZEX;
		int32 y = posY / TILE_SIZEY;

		// test
		// * 마우스 위치에 해당하는 타일을 불러옵니다.
		Tile* tile = _tilemap->GetTileAt({ x, y });
		
		if (tile)
		{
			// 타일의 정보를 수정합니다.
			tile->value = 1;
		}
	}
}
