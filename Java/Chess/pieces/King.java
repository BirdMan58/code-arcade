package pieces;

import java.util.ArrayList;

import main.GamePanel;

public class King extends Piece {

	public King(int row, int col, boolean isWhite, GamePanel panel){
		super(row, col, isWhite, panel);
		type = PieceType.KING;
		image = panel.setImg(type, isWhite);	
	}

	@Override
	public ArrayList<Move> getMoves() {

		int tempRow, tempCol;
		
		tempCol = col - 1;
		for(int i = 0; i < 3; i++) {
			tempRow = row - 1;
			for(int j = 0; j < 3; j++) {
				if(tempRow == row && tempCol == col) {
					tempRow++;
					continue;
				}
				addMove(tempRow, tempCol);
				tempRow++;
			}
			tempCol++;
		}

		return moves;
	}

	// public boolean isKingInCheck() {
	// 	//Look for enemy pieces from vertical and horizontal path
	// 	//Eg: from rook and queen
	// 	Piece temPiece = checkPath(0, 1);
	// 	temPiece = checkPath(0, 1);
	// 	temPiece = checkPath(0, 1);
	// 	temPiece = checkPath(0, 1);
	// 	return true;
	// }

	// public Piece checkPath(int xDirection, int yDirection) {
	// 	int tempRow = row;
	// 	int tempCol = col;
		
	// 	while(tempRow >= 0 && tempRow <= 7 && tempCol >= 0 && tempCol <= 7) {
	// 		tempRow += yDirection;
	// 		tempCol += xDirection;
			
	// 		Piece tempPiece = isHittingPiece(tempRow, tempCol);
	// 		if(tempPiece != null && (tempPiece.isWhite ^ this.isWhite)) {
	// 			return tempPiece;
	// 		}
	// 	}
	// 	return null;
	// }
}
