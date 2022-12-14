#include "objModel.h"
#include"TextureManager.h"
#include"AliceFunctionUtility.h"
#include"DefaultMaterial.h"


void objModel::Create(const char* filePath, bool smoothing, ModelData* data)
{
	std::vector<std::string> files;
	files = AliceFunctionUtility::getFileNames(filePath);
	std::string fileName;

	for (std::string file : files)
	{
		if (file.find("obj") != std::string::npos)
		{
			fileName = file;
		}

	}
	//ファイルストリーム
	std::ifstream file;
	//objファイルを開く
	file.open(fileName);
	//ファイルオープン失敗をチェック
	if (file.fail())
	{
		assert(0);
	}

	//頂点座標
	std::vector<AliceMathF::Vector3> positions;
	//法線ベクトル
	std::vector<AliceMathF::Vector3> normals;
	//テクスチャUV
	std::vector<AliceMathF::Vector2> texcoords;

	PosNormalUv tmp = { {},{},{} };

	//1行ずつ読み込む
	std::string line;
	while (std::getline(file, line))
	{
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		//半角スペース区切りで行の先頭文字を取得
		std::string key;
		std::getline(line_stream, key, ' ');

		//先頭文字列がmtllibならマテリアル
		if (key == "mtllib")
		{
			//マテリアルのファイル名読み込み
			std::string filename;
			line_stream >> filename;
			//マテリアル読み込み
			LoadMaterial(filePath, filename, data);

		}
		//先頭文字列がVなら頂点座標
		if (key == "v")
		{
			//X,Y,Z座標読み込み
			AliceMathF::Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			//座標データに追加
			positions.emplace_back(position);
		}
		//先頭文字列がvtならテクスチャ
		if (key == "vt")
		{
			//U,V成分読み込み
			AliceMathF::Vector2 texcoord;
			line_stream >> texcoord.x;
			line_stream >> texcoord.y;
			//V方向反転
			texcoord.y = 1.0f - texcoord.y;
			//テクスチャ座標データに追加
			texcoords.emplace_back(texcoord);
		}
		//先頭文字列がvnなら法線ベクトル
		if (key == "vn")
		{
			//X,Y,Z成分読み込み
			AliceMathF::Vector3 normal{};
			line_stream >> normal.x;
			line_stream >> normal.y;
			line_stream >> normal.z;
			//法線ベクトルデータに追加
			normals.emplace_back(normal);
		}
		//先頭文字ならポリゴン(三角形)
		if (key == "f")
		{
			//半角スペース区切りで行の続きを読み込む
			std::string index_string;
			while (std::getline(line_stream, index_string, ' '))
			{
				//頂点インデックス1個分文字列をストリームに変換して解析しやすくする
				std::istringstream index_stream(index_string);
				uint16_t indexPosition, indexTexcoord, indexNormal;
				index_stream >> indexPosition;
				//スラッシュを飛ばす
				index_stream.seekg(1, std::ios_base::cur);
				index_stream >> indexTexcoord;
				//スラッシュを飛ばす
				index_stream.seekg(1, std::ios_base::cur);
				index_stream >> indexNormal;

				//頂点データの追加
				tmp.pos = positions[static_cast<size_t>(indexPosition) - 1];
				tmp.normal = normals[static_cast<size_t>(indexNormal) - 1];
				tmp.uv = texcoords[static_cast<size_t>(indexTexcoord) - 1];
				data->vertices.push_back(tmp);

				if (smoothing)
				{
					data->smoothData[static_cast<size_t>(indexPosition)].emplace_back(static_cast<uint32_t>(data->vertices.size()-1));
				}

				//インデックスデータの追加
				data->indices.emplace_back(static_cast<uint32_t>(data->indices.size()));

			}
		}
	}

	//ファイルを閉じる
	file.close();

	if (smoothing)
	{
		CalculateSmoothedVertexNormals(data);
	}

	data->maxVert = static_cast<UINT>(data->vertices.size());
	data->maxIndex = static_cast<UINT>(data->indices.size());

	//頂点バッファ・インデックス生成
	data->vertexBuffer = std::make_unique<ComputeVertexBuffer>();
	data->vertexBuffer->Create(data->maxVert, sizeof(PosNormalUv));

	data->indexBuffer = std::make_unique<IndexBuffer>();
	data->indexBuffer->Create(data->maxIndex);

	//頂点バッファへのデータ転送
	data->vertexBuffer->Update(data->vertices.data());

	//インデックスバッファへのデータ転送
	data->indexBuffer->Update(data->indices.data());

	//マテリアル用定数バッファ生成
	data->constBuffMaterial = std::make_unique<ConstantBuffer>();
	data->constBuffMaterial->Create(sizeof(ConstBuffDataMaterial));
	ConstBuffDataMaterial tmpMaterial = data->modelMaterial.GetConstBuffMaterial();
	data->constBuffMaterial->Update(&tmpMaterial);

	//ポリゴン爆散用定数バッファ生成
	data->constBuffVelocity = std::make_unique<ConstantBuffer>();
	data->constBuffVelocity->Create(sizeof(float));
	float zero = 0.0f;
	data->constBuffVelocity->Update(&zero);

	//コンピュートシェーダ用入力バッファ生成
	data->csInputVer = std::make_unique<StructuredBuffer>();
	data->csInputVer->Create(data->vertices.size(), sizeof(PosNormalUv));

	//コンピュートシェーダ用ブレンドバッファ生成
	data->csInputBlendVer = std::make_unique<StructuredBuffer>();
	data->csInputBlendVer->Create(data->vertices.size(), sizeof(PosNormalUv));

	//コンピュートシェーダ用タイム定数バッファ生成
	data->csTime = std::make_unique<ConstantBuffer>();
	data->csTime->Create(sizeof(float));
}

void objModel::LoadMaterial(const std::string& directoryPath, const std::string& filename,ModelData* data)
{
	std::ifstream file;

	std::string filePath = directoryPath + "/" + filename;

	file.open(filePath);
	if (file.fail())
	{
		assert(0);
	}

	std::string line;
	while (std::getline(file, line))
	{
		//1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		//半角スペース区切りで行の先頭文字を取得
		std::string key;
		std::getline(line_stream, key, ' ');

		if (key[0] == '\t')
		{
			key.erase(key.begin());
		}

		if (key == "newmtl")
		{
			line_stream >> data->modelMaterial.name;
		}
		if (key == "Ka")
		{
			line_stream >> data->modelMaterial.ambient.x;
			line_stream >> data->modelMaterial.ambient.y;
			line_stream >> data->modelMaterial.ambient.z;
		}
		if (key == "Kd")
		{
			line_stream >> data->modelMaterial.diffuse.x;
			line_stream >> data->modelMaterial.diffuse.y;
			line_stream >> data->modelMaterial.diffuse.z;
		}
		if (key == "Ks")
		{
			line_stream >> data->modelMaterial.specular.x;
			line_stream >> data->modelMaterial.specular.y;
			line_stream >> data->modelMaterial.specular.z;
		}
		if (key == "map_Kd")
		{
			line_stream >> data->modelMaterial.textureFiename;
			LoadTexture(directoryPath, data->modelMaterial.textureFiename, data);
		}
	}

	//ファイルを閉じる
	file.close();
}

void objModel::LoadTexture(const std::string& directoryPath, const std::string& filename,ModelData* data)
{
	std::string filepath = directoryPath + "/" + filename;

	uint32_t handl = TextureManager::Load(filepath);

	data->textureData = TextureManager::GetTextureData(handl);
}

void objModel::CalculateSmoothedVertexNormals(ModelData* data)
{
	auto itr = data->smoothData.begin();
	for (;itr != data->smoothData.end(); itr++)
	{
		//各面用の共通点コレクション
		std::vector<uint32_t>& v = itr->second;
		//全頂点の法線を平均する
		AliceMathF::Vector3 normal = {};
		for (uint32_t index : v)
		{
			normal += AliceMathF::Vector3{ data->vertices[index].normal.x,  data->vertices[index].normal.y,  data->vertices[index].normal.z};
		}

		normal = normal / static_cast<float>(v.size());
		normal.Normal();
		//共通法線を使用する全ての頂点データに書き込む
		for (uint32_t index : v)
		{
			data->vertices[index].normal = { normal.x,normal.y,normal.z };
		}

	}
}