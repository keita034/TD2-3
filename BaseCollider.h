#pragma once

#include "CollisionTypes.h"
#include "CollisionInfo.h"
#include "Player.h"

/// <summary>
/// �R���C�_�[���N���X
/// </summary>
class BaseCollider
{
public:
	BaseCollider() = default;
	virtual ~BaseCollider() = default;

	inline void SetObject(Player* player) {
		this->player = player;
	}

	inline Player* GetObject3d() {
		return player;
	}

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;

	inline CollisionShapeType GetShapeType() { return shapeType; }
	
	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	/// <param name="info">�Փˏ��</param>
	inline void OnCollision(const CollisionInfo& info) {
		player->OnCollision(info);
	}

protected:
	Player* player = nullptr;
	// �`��^�C�v
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
};

