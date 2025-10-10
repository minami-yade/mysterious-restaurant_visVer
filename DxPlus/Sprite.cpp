﻿// ============================================================================
// OIC教材用モジュール - 大阪情報コンピュータ専門学校
// 作成者：Y.Tanaka
// このファイルは授業用教材として作成されています。
// ============================================================================

#include "Sprite.h"
#include "Utils.h"

namespace DxPlus::Sprite
{
    // ============================================================================
    // スプライト画像の読み込み
    // ============================================================================
    int Load(const std::wstring& filePath, const Vec2& texPos, const Vec2& texSize)
    {
        // 画像全体を一度読み込む
        int textureID = LoadGraph(filePath.c_str());
        if (textureID == -1) return -1; // ロードに失敗した場合

        // テクスチャのサイズが指定されていない場合、画像全体を使用
        Vec2 finalTexSize = texSize;
        if (finalTexSize.x == 0.0f && finalTexSize.y == 0.0f)
        {
            int width, height;
            GetGraphSize(textureID, &width, &height);
            finalTexSize = Vec2(static_cast<float>(width), static_cast<float>(height));
        }

        // 指定された範囲を新しいグラフィックハンドルとして切り出す
        int spriteID = DerivationGraph(
            static_cast<int>(texPos.x),
            static_cast<int>(texPos.y),
            static_cast<int>(finalTexSize.x),
            static_cast<int>(finalTexSize.y),
            textureID
        );

        // 元のテクスチャを削除（不要な場合）
        DeleteGraph(textureID);

        return spriteID; // 新しいスプライトのIDを返す
    }

    // ============================================================================
    // スプライトを描画（回転・拡大縮小・色つき対応）
    // ============================================================================
    void Draw(int spriteID, const Vec2& position, const Vec2& scale, const Vec2& center, float rotationZ, int color)
    {
        int roundedX = static_cast<int>(std::round(position.x));
        int roundedY = static_cast<int>(std::round(position.y));
        int roundedCenterX = static_cast<int>(std::round(center.x));
        int roundedCenterY = static_cast<int>(std::round(center.y));

        // 色を設定
        SetDrawBright(Utils::GetColorR(color), Utils::GetColorG(color), Utils::GetColorB(color));

        // スプライトを描画
        DrawRotaGraph3(
            roundedX,
            roundedY,
            roundedCenterX,
            roundedCenterY,
            static_cast<double>(scale.x),
            static_cast<double>(scale.y),
            static_cast<double>(rotationZ),
            spriteID,
            TRUE
        );

        // 色をリセット
        SetDrawBright(255, 255, 255);
    }

    // ============================================================================
    // スプライトを敷き詰めて描画（背景・地面タイル向け）
    // ============================================================================
    void DrawTiledRect(int spriteID, const Vec2& position, const Vec2& size, const Vec2& pivot, int color)
    {
        // スプライトの幅と高さを取得
        int spriteWidth, spriteHeight;
        GetGraphSize(spriteID, &spriteWidth, &spriteHeight);

        // 描画領域内での基準点を考慮した描画開始位置を計算
        int drawPosX = static_cast<int>(position.x - pivot.x);
        int drawPosY = static_cast<int>(position.y - pivot.y);

        // 横方向と縦方向のタイル数を計算
        int tilesX = static_cast<int>(size.x / spriteWidth);
        int tilesY = static_cast<int>(size.y / spriteHeight);

        // 描画範囲の残り幅と高さ（端の部分を切り取るための計算）
        int remainingWidth = static_cast<int>(size.x) % spriteWidth;
        int remainingHeight = static_cast<int>(size.y) % spriteHeight;

        // 色を設定
        SetDrawBright(Utils::GetColorR(color), Utils::GetColorG(color), Utils::GetColorB(color));

        // タイル描画のループ
        for (int y = 0; y <= tilesY; ++y)
        {
            for (int x = 0; x <= tilesX; ++x)
            {
                // もし最後の列で残り幅が0なら描画をスキップ
                if (x == tilesX && remainingWidth == 0) {
                    continue;  // 描画をスキップ
                }

                // 各タイルの描画位置
                int currentDrawPosX = drawPosX + x * spriteWidth;
                int currentDrawPosY = drawPosY + y * spriteHeight;

                // 描画する幅と高さ
                int drawWidth = spriteWidth;
                int drawHeight = spriteHeight;

                // 最後の列なら、余った幅だけ描画
                if (x == tilesX && remainingWidth > 0) {
                    drawWidth = remainingWidth;
                }

                // 最後の行なら、余った高さだけ描画
                if (y == tilesY && remainingHeight > 0) {
                    drawHeight = remainingHeight;
                }

                // 描画範囲内に収まっているかを確認
                if (currentDrawPosX + drawWidth <= position.x + size.x &&
                    currentDrawPosY + drawHeight <= position.y + size.y)
                {
                    // テクスチャの一部を描画
                    DrawRectGraph(
                        currentDrawPosX, currentDrawPosY,   // 描画位置
                        0, 0,                              // テクスチャの描画開始位置
                        drawWidth, drawHeight,              // 描画するテクスチャの幅と高さ
                        spriteID, TRUE                      // スプライトIDと透過設定
                    );
                }
            }
        }

        // 色をリセット
        SetDrawBright(255, 255, 255);
    }

    // ============================================================================
    // スプライトの削除（グラフィックハンドル解放）
    // ============================================================================
    void Delete(int spriteID)
    {
        // グラフィックハンドルを削除
        DeleteGraph(spriteID);
    }

    // ============================================================================
    // SpriteBase メンバ関数実装
    // ============================================================================

    void SpriteBase::SetID(int newID, DxPlus::Vec2 pivot)
    {
        id = newID;
        center = pivot;
    }

    // スプライトクラス
    void SpriteBase::Draw(const Vec2& position, const Vec2& scale, float rotationZ, int color) const
    {
        if (id != -1)
        {
            DxPlus::Sprite::Draw(id, position, scale, center, rotationZ, color);
        }
    }

    void SpriteBase::Delete()
    {
        if (id != -1)
        {
            DxPlus::Sprite::Delete(id);
            id = -1;
        }
    }

    bool SpriteBase::LoadImage(const std::wstring& path, Vec2 autoCenter)
    {
        int w = 0, h = 0;
        id = DxPlus::Sprite::Load(path);
        if (id == -1) return false;
        if (DxLib::GetGraphSize(id, &w, &h) != 0) return false;
        center = { w * autoCenter.x, h * autoCenter.y };
        return true;
    }

    // ============================================================================
    // 各派生クラスの Load 実装
    // ============================================================================

    bool SpriteLeftTop::Load(const std::wstring& path)
    {
        return LoadImage(path, { 0.0f, 0.0f });
    }

    bool SpriteCenter::Load(const std::wstring& path)
    {
        return LoadImage(path, { 0.5f, 0.5f });
    }

    bool SpriteBottom::Load(const std::wstring& path)
    {
        return LoadImage(path, { 0.5f, 1.0f });
    }

    bool SpriteCustom::Load(const std::wstring& path, DxPlus::Vec2 c)
    {
        return LoadImage(path, c);
    }
}
