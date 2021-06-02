#include "Rank.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Input.h"
#include "Game.h"

static int mImageHandle; //画像ハンドル格納用変数
static int WaitTime; //ランキング表示時間
struct RankingData Ranking[RANKCOUNT]; // ランキングデータ変数宣言


/***********************************************
 * ランキング画面 初期化
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Rank_Initialize() {
	mImageHandle = LoadGraph("images/Scene_Rank.png");//画像のロード
	WaitTime = 0;
	Rank_Read();
}


/***********************************************
 * ランキング画面 終了処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Rank_Finalize() {
	DeleteGraph(mImageHandle);//画像の解放
}


/***********************************************
 * ランキング画面 更新
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Rank_Update() {
	if (iKeyFlg == PAD_INPUT_B || CheckHitKey(KEY_INPUT_ESCAPE) != 0) { //Bボタンが押されていたら
			SceneMgr_ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
}


/***********************************************
 * ランキングデータ描画
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Rank_Draw() {
	//ランキング画像表示
	DrawGraph(0, 0, mImageHandle, FALSE);
	// ランキング一覧を表示
	SetFontSize(24);
	for (int i = 0; i < RANKCOUNT; i++) {
		DrawFormatString(240, 180 + i * 25, GetColor(255, 255, 255), "%2d %10s %12d",
			Ranking[i].no, Ranking[i].name, Ranking[i].score);
	}

	// 文字の表示(点滅)
	if (++WaitTime < 50) {
		SetFontSize(16);
		DrawString(200, 460, "EscキーまたはBボタンを押すとメニュー画面に戻ります。",
			GetColor(255, 255, 255));
	}
	else if (++WaitTime > 100) {
		WaitTime = 0;
	}
}


/***********************************************
 * ランキング入力処理
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Rank_Input()
{
	//ランキング画像表示
	DrawGraph(0, 0, mImageHandle, FALSE);

	// フォントサイズの設定
	SetFontSize(20);
	// 名前入力指示文字列の描画
	DrawString(150, 240, "ランキングに登録します", GetColor(0, 0, 0));
	DrawString(150, 270, "名前を英字(10文字以内)で入力してください", GetColor(0, 0, 0));

	// 名前の入力
	DrawString(150, 310, "> ", GetColor(0, 0, 0));
	DrawBox(160, 305, 300, 335, GetColor(0, 0, 0), TRUE);
	KeyInputSingleCharString(170, 310, 10, Ranking[(RANKCOUNT - 1)].name, FALSE);
	Ranking[(RANKCOUNT - 1)].score = Game_GetScore(); //ランキングデータの最後にスコアを登録
	Ranking[(RANKCOUNT - 1)].no = RANKCOUNT; //ランキングNo.は最後にしておく

	Rank_Sort(); // ランキング並べ替え
	Rank_Save(); // ランキングデータの保存

	SceneMgr_ChangeScene(eScene_Rank); //ランキング表示画面へ移行
}


/***********************************************
 * ランキング並べ替え
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Rank_Sort()
{
	int i, j;
	RankingData work;
	// 選択法ソート
	for (i = 0; i < RANKCOUNT; i++) {
		for (j = i + 1; j < RANKCOUNT; j++) {
			if (Ranking[i].score <= Ranking[j].score) {
				work = Ranking[i];
				Ranking[i] = Ranking[j];
				Ranking[j] = work;
			}
		}
	}
	// 順位付け
	for (i = 0; i < RANKCOUNT; i++) {
		Ranking[i].no = 1;
	}
	// 得点が同じ場合は、同じ順位とする
	// 同順位があった場合の次の順位はデータ個数が加算された順位とする
	for (i = 0; i < RANKCOUNT; i++) {
		for (j = i + 1; j < RANKCOUNT; j++) {
			if (Ranking[i].score > Ranking[j].score) {
				Ranking[j].no++;
			}
		}
	}
}


/***********************************************
 * ランキングデータの保存
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Rank_Save()
{
	FILE* fp;
	// ファイルオープン
	fopen_s(&fp, RANKING_FILE, "w");;
	if (fp != NULL) {
		// ランキングデータ分配列データを書き込む
		for (int i = 0; i < RANKCOUNT; i++) {
			fprintf(fp, "%s %d %d\n", Ranking[i].name, Ranking[i].no, Ranking[i].score);
		}
		//ファイルクローズ
		fclose(fp);
	}
	else {
		//エラー処理 (必要に応じて作成）
		// printf("Ranking Data Error\n");
	}
}

/***********************************************
 * ランキングデータ読み込み
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void Rank_Read()
{
	FILE* fp;
	int i;
	//ファイルオープン
	fopen_s(&fp, RANKING_FILE, "r");
	if (fp != NULL) {
		//ランキングデータ配分列データを読み込む
		for (int i = 0; i < RANKCOUNT; i++) {
			fscanf_s(fp, "%s %d %d", Ranking[i].name, 10, &Ranking[i].no, &Ranking
				[i].score);
		}
		fclose(fp);
	}
	else { //ファイルがオープンできないor読み込めない
	//エラー処理 (必要に応じて作成）
	// printf("Ranking Data Error\n");
	// ランキングデータの初期化
		for (i = 0; i < RANKCOUNT; i++) {
			Ranking[i].no = (i + 1);
			sprintf_s(Ranking[i].name, "...");
			Ranking[i].score = 1;
		}
	}
}
