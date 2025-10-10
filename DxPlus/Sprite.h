// ============================================================================
// OIC教材用モジュール - 大阪情報コンピュータ専門学校
// 作成者：Y.Tanaka
// このファイルは授業用教材として作成されています。
// ============================================================================

#pragma once
#include <string>
#include "DxLib.h"
#include "Vector2.h"
#include "Utils.h"

namespace DxPlus::Sprite
{
    // ============================================================================
    // グラフィックハンドルを読み込み、必要に応じて切り出す
    // ============================================================================
    /// <summary>
    /// 画像を読み込む
    /// </summary>
    /// <param name="filePath">画像ファイルのパス</param>
    /// <param name="texPos">使用する部分の左上の座標</param>
    /// <param name="texSize">幅と高さ</param>
    /// <returns>画像のID</returns>
    int Load(const std::wstring& filePath,
        const Vec2& texPos = Vec2(0.0f, 0.0f),
        const Vec2& texSize = Vec2(0.0f, 0.0f)
    );

    // ============================================================================
    // スプライトを描画する関数
    // ============================================================================
    /// <summary>
    /// スプライトを描画する
    /// </summary>
    /// <param name="spriteID">描画するスプライトのID</param>
    /// <param name="position">スプライトを描画する位置</param>
    /// <param name="scale">スプライトの拡大縮小率（デフォルトは1.0で等倍）</param>
    /// <param name="center">スプライトの回転中心（デフォルトはスプライトの左上）</param>
    /// <param name="rotationZ">Z軸周りの回転角度（デフォルトは0.0）</param>
    /// <param name="color">スプライトの色（デフォルトは白）</param>
    void Draw(int spriteID, 
        const Vec2& position = Vec2(0, 0),
        const Vec2& scale = Vec2(1.0f, 1.0f),
        const Vec2& center = Vec2(0.0f, 0.0f),
        float rotationZ = 0.0f,
        int color = GetColor(255, 255, 255));

    void DrawTiledRect(
        int spriteID, const Vec2& position,
        const Vec2& size = Vec2(1.0f, 1.0f),
        const Vec2& pivot = Vec2(0.0f, 0.0f),
        int color = GetColor(255, 255, 255));

    /// <summary>
    /// スプライトの削除関数
    /// </summary>
    /// <param name="spriteID">スプライトのID</param>
    void Delete(int spriteID);

    // ============================================================================
    // スプライトクラス（基底）
    // ============================================================================
    class SpriteBase
    {
    public:
        SpriteBase() = default;
        virtual ~SpriteBase() { Delete(); }
        void SetID(int newID, DxPlus::Vec2 pivot);
        bool IsLoaded() const { return id != -1; }
        void Draw(const Vec2& position, const Vec2& scale = { 1,1 }, float rotationZ = 0.0f, int color = DxLib::GetColor(255, 255, 255)) const;
        void Delete();
    protected:
        int id = -1;
        DxPlus::Vec2 center = { 0.0f, 0.0f };
        bool LoadImage(const std::wstring& path, Vec2 autoCenter);
    };

    // ============================================================================
    // スプライト：左上が中心（デフォルト）
    // ============================================================================
    class SpriteLeftTop : public SpriteBase
    {
    public:
        bool Load(const std::wstring& path);
        static DxPlus::Vec2 DefaultPivot() { return { 0.0f, 0.0f }; }
    };

    // ============================================================================
    // スプライト：中央が中心（プレイヤー・敵キャラ向け）
    // ============================================================================
    class SpriteCenter : public SpriteBase
    {
    public:
        bool Load(const std::wstring& path);
        static DxPlus::Vec2 DefaultPivot() { return { 0.5f, 0.5f }; }
    };

    // ============================================================================
    // スプライト：足元が中心（立ちキャラ・キャラ接地向け）
    // ============================================================================
    class SpriteBottom : public SpriteBase
    {
    public:
        bool Load(const std::wstring& path);
        static DxPlus::Vec2 DefaultPivot() { return { 0.5f, 1.0f }; }
    };

    // ============================================================================
    // スプライト：任意の中心点を指定可能
    // ============================================================================
    class SpriteCustom : public SpriteBase
    {
    public:
        bool Load(const std::wstring& path, DxPlus::Vec2 center);
    };

    template <typename T>
    void LoadDivSprite(const std::wstring& filePath, int num, int numX, int numY, int sizeX, int sizeY, T spriteArray[])
    {
        int tempIDs[256];
        if (num > 256)
        {
            Utils::FatalError(L"Too many sprites for LoadDivSprite");
            return;
        }

        int result = DxLib::LoadDivGraph(filePath.c_str(), num, numX, numY, sizeX, sizeY, tempIDs);
        if (result == -1)
        {
            DxPlus::Utils::FatalError((std::wstring(L"Failed to load:") + filePath).c_str());
            return;
        }

        for (int i = 0; i < num; ++i)
        {
            spriteArray[i] = T();

            int w = 0, h = 0;
            DxLib::GetGraphSize(tempIDs[i], &w, &h);
            Vec2 pixelCenter = { w * T::DefaultPivot().x, h * T::DefaultPivot().y };

            spriteArray[i].SetID(tempIDs[i], pixelCenter);
        }
    }
}
