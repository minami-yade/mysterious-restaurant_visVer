// ============================================================================
// OIC教材用モジュール - 大阪情報コンピュータ専門学校
// 作成者：Y.Tanaka
// このファイルは授業用教材として作成されています。
// ============================================================================

#pragma once
#include <string>
#include "DxLib.h"
#include "Vector2.h"

namespace DxPlus::Text
{
    static int defaultFontHandle = -1;

    enum TextAlign
    {
        TOP_LEFT,
        TOP_CENTER,
        TOP_RIGHT,
        MIDDLE_LEFT,
        MIDDLE_CENTER,
        MIDDLE_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT
    };

    void InitializeDefaultFont(const wchar_t* fontName, int fontSize, int fontThickness);
    void FinalizeFont();
    int InitializeFont(const wchar_t* fontName, int fontSize, int fontThickness);
    void DeleteFont(int fontHandle);

    void DrawString(
        const wchar_t* text,
        Vec2 position,
        int color = GetColor(255, 255, 255),
        TextAlign align = TextAlign::TOP_LEFT,
        Vec2 scale = { 1.0f, 1.0f },
        double angle = 0.0,
        int fontHandle = -1);

    void DrawString(
        const wchar_t* text,
        int x,
        int y,
        int color = GetColor(255, 255, 255),
        TextAlign align = TextAlign::TOP_LEFT,
        double scaleX = 1.0,
        double scaleY = 1.0,
        double angle = 0.0,
        int fontHandle = -1);

    std::wstring Format(const wchar_t* format, ...);

    void DrawTextWithAutoWrap(
        const wchar_t* text,
        const DxPlus::Vec2& position,
        const DxPlus::Vec2& size,
        int framePerChar,
        int color,
        int lineSpacing
    );

    // UTF-8 文字列を UTF-16 文字列に変換
    std::wstring Utf8ToUtf16(const std::string& utf8);
}
