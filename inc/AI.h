#include <stdlib.h>
#include <vector>
#include "Board.h"
#include "Tree.h"

#define SCORE_WIN 100000
#define SCORE_LOSE -100000

class StarTech {
private:
	Tree<Board> treeBoard;
	int depthSI;
	bool whiteSI;
public:
	StarTech(int d, bool white = false):depthSI(d), whiteSI(white){
		Board board;
		treeBoard.setRoot(new TreeNode<Board>(board));
	}

	int getScore(const Board & tempBoard) const{ //zwracanie wartosci planszy (ocena wg SI)
		if (tempBoard.isDraw()) return 0;
		int score = 0;
		bool flagNoWhite = true;
		bool flagNoBlack = true;
		for (int i = 0; i < 8; i++){
			for (int j = 0; j < 8; j++){
				if ((i+j)%2==0){
					switch(tempBoard.getSafe(i,j)){
						case white: 	flagNoWhite=false; score-=30; 	break;
						case whiteKing: flagNoWhite=false; score-=50; 	break;
						
						case black: 	flagNoBlack=false; score+=30; 	break;
						case blackKing: flagNoBlack=false; score+=50; 	break;
					}
				}
				if(tempBoard.getSafe(i,j)==black) score += 7-j;
				else if(tempBoard.getSafe(i,j)==white) score -= j;
			}
		}
		if (flagNoWhite) score = SCORE_WIN;
		if (flagNoBlack) score = SCORE_LOSE;
		if (whiteSI) score *= -1;
		return score;
	}
	
	/*int minmax(TreeNode<Board> * ptr, int depth, int alpha, int beta) const
	{
		if(depth == 0 || ptr->getChild().empty()) return getScore(ptr->getValue());
	
		if(ptr->getValue().whiteTurn){
			int minScore = SCORE_WIN;
			for(int k = 0; k < ptr->getChild().size(); k++){
				int score = minmax(ptr->getChild(k), depth-1, alpha, beta);
				minScore = min(minScore, score);
				beta = min(beta, minScore);
				if (beta <= alpha) break;
			}
			return minScore;
		}
		else{
			int maxScore = SCORE_LOSE;
			for(int k = 0; k < ptr->getChild().size(); k++){
				int score = minmax(ptr->getChild(k), depth-1, alpha, beta);
				maxScore = max(maxScore, score);
				alpha = max(alpha, maxScore);
				if (beta <= alpha) break;
			}
			return maxScore;
		}
	}*/
	
	void allLegalCaptures2(TreeNode<Board> * ptr, int i1, int j1, const Board & boardNow){ //wykonywanie wszystkich mozliwych bic
		Board board2(boardNow);
		for (int i2 = -2; i2 <= 2; i2+=4){
			for (int j2 = -2; j2 <= 2; j2+=4){
				if (board2.legalCapture(i1, j1, i1+i2, j1+j2)){
					Board tempBoard(board2);
					tempBoard.move(i1, j1, i1+i2, j1+j2);
					
					if (tempBoard.canCapture(i1+i2, j1+j2)){
						allLegalCaptures2(ptr, i1+i2, j1+j2, tempBoard);
					} 
					else{
						tempBoard.whiteTurn = !tempBoard.whiteTurn;
						tempBoard.checkPromotion();
						ptr->addChild(tempBoard);
					}
				}
			}
		}				
	}
	
	void allLegalSteps2(TreeNode<Board> * ptr, int i1, int j1){ //wykonywanie wszystkich mozliwych przesuniec pionkow
		Board board2(ptr->getValue());
		for (int i2 = -1; i2 <= 1; i2+=2){
			for (int j2 = -1; j2 <= 1; j2+=2){
				if (board2.legalStep(i1, j1, i1+i2, j1+j2)){
					Board tempBoard(board2);
					tempBoard.move(i1, j1, i1+i2, j1+j2);
					
					tempBoard.whiteTurn = !tempBoard.whiteTurn;
					tempBoard.checkPromotion();
					ptr->addChild(tempBoard);
				}
			}
		}
	}
	
	void moveTree(TreeNode<Board> * ptr, int depth){ //generowanie drzewa ruchow o glebokosci depth od elementu ptr drzewa
		Board board = ptr->getValue();
		bool flagCanCapture = board.canCapture();
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 8; j++){
				if ((i+j) % 2 == 0){
					if (board.isFriendly(i,j)){
						if (board.canCapture(i, j)){
							allLegalCaptures2(ptr, i, j, ptr->getValue());
						}
						else if (!flagCanCapture){
							if (board.canStep(i, j)){
								allLegalSteps2(ptr, i, j);
							}
						}
					}
				}
			}
		}
		
		if (depth-1 > 0){
			for(int k = 0; k < ptr->getChild().size(); k++){
				moveTree(ptr->getChild(k), depth-1);
			}
		}
	}
	
	/*void moveTreeGrow(TreeNode<Board> * ptr){
		int childSize = ptr->getChild().size();
		if (childSize > 0){
			for(int k = 0; k < childSize; k++){
				moveTreeGrow(ptr->getChild(k));
			}
		}
		else{
			moveTree(ptr, 2);
		}
	}
	
	int find(const Board & board2){
		int childSize = treeBoard.getRoot()->getChild().size();
		for(int k = 0; k < childSize; k++){
			if (treeBoard.getRoot()->getChild(k)->getValue() == board2){
				return k;
			}
		}
		return -1;
	}
	
	void cut(int k){
		if (k < 0) return;//throw std::out_of_range("error");
		 
		TreeNode<Board> * ptrFutureRoot = treeBoard.getRoot()->getChild(k);
		treeBoard.getRoot()->removeChild(k);
		delete treeBoard.getRoot();
		treeBoard.setRoot(ptrFutureRoot);
	}
	
	Board playOLD(const Board & board2){
		cut(find(board2));
		//treeBoard.getRoot()->getValue().print();
		//std::cout << "CUT!!! height: " << treeBoard.height(treeBoard.getRoot()) << std::endl;
		moveTreeGrow(treeBoard.getRoot());
		//treeBoard.getRoot()->getChild(0)->getValue().print();
		//std::cout << "GROWN!!! height: " << treeBoard.height(treeBoard.getRoot()) << std::endl;
		int bestMove = 0;
		int bestScore = SCORE_LOSE;
		std::vector<int> boardIdVector;
		if (treeBoard.getRoot()->getChild().size() == 1){
			bestMove = 0;
		}
		else
		for (int k = 0; k < treeBoard.getRoot()->getChild().size(); k++)
		{
			int tempScore = minmax(treeBoard.getRoot()->getChild(k), depthSI, SCORE_LOSE, SCORE_WIN);
			if(bestScore < tempScore){
				bestScore = tempScore;
				bestMove = k;
				boardIdVector.clear();
				boardIdVector.push_back(k);
			}
			else if (bestScore == tempScore){
				bestScore = tempScore;
				bestMove = k;
				boardIdVector.push_back(k);
			}
		}
		if (boardIdVector.size() > 0){
			bestMove = boardIdVector[rand() % boardIdVector.size()];
		}
		cut(bestMove);
		std::cout << "Draw: " << treeBoard.getRoot()->getValue().getDraw() << std::endl;
		return treeBoard.getRoot()->getValue();
	}*/
	
	Board play(const Board & board2){ //Metoda wykonajuca ruch SI
		int bestMove = 0;
		int bestScore = SCORE_LOSE;
		std::vector<int> boardIdVector;
		treeBoard.clear();
		treeBoard.setRoot(board2);
		moveTree(treeBoard.getRoot(), 1);
		
		if(treeBoard.getRoot()->getChild().size() == 1){ //Jeśli jest jeden ruch do wyboru, wybiera go bez Min-Max
			bestMove = 0;
			//std::cout << "BestScore: ???"  << std::endl;
		}
		else{
			for (int k = 0; k < treeBoard.getRoot()->getChild().size(); k++)
			{
				int tempScore = minmax(treeBoard.getRoot()->getChild(k), depthSI, bestScore, SCORE_WIN); //Spawdzanie, ktora z opcji jest najlepsza przy pomocy min-max'a z alfa-beta cieciami
				if(bestScore < tempScore){
					bestScore = tempScore;
					bestMove = k;
					boardIdVector.clear();
					boardIdVector.push_back(k);
				}
				else if (bestScore == tempScore){
					bestScore = tempScore;
					bestMove = k;
					boardIdVector.push_back(k);
				}
			}
			if (boardIdVector.size() > 0){
				bestMove = boardIdVector[rand() % boardIdVector.size()];
			}
			//std::cout << "BestScore: " << bestScore  << std::endl;
		}
		//std::cout << "Draw: " << treeBoard.getRoot()->getValue().getDraw() << std::endl;
		
		return treeBoard.getRoot()->getChild(bestMove)->getValue();
	}
	
	int minmax(TreeNode<Board> * ptr, int depth, int alpha, int beta) //metoda Min-Max z alfa-beta cieciami
	{
		if(depth == 0 || ptr->getValue().end()) return getScore(ptr->getValue());
		
		moveTree(ptr, 1);
		
		int tempScore = SCORE_LOSE; 
		if(ptr->getValue().whiteTurn) tempScore = SCORE_WIN;
		
		for(int k = 0; k < ptr->getChild().size(); k++){
			int score = minmax(ptr->getChild(k), depth-1, alpha, beta);
			
			if(ptr->getValue().whiteTurn){
				tempScore = min(tempScore, score);
				beta = min(beta, tempScore);
			}
			else{
				tempScore = max(tempScore, score);
				alpha = max(alpha, tempScore);
			}
			if (beta <= alpha) break;
		}
		return tempScore;
	}
};
