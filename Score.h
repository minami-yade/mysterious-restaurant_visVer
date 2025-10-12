#pragma once

// --- 画像読み込み関係 ---
void ScoreImage();

// --- リセット関数（初期配置や状態の初期化） ---
void ScoreReset();

// --- 動きの更新（単純な三角波で上下） ---
void UpdateScore(float deltaTime);

// --- 描画関数 ---
void ScoreDraw();

// --- 解放関数 ---
void ScoreDelete();
