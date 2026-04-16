package pieces;

import java.util.ArrayList;

import main.GamePanel;

public class Pawn extends Piece {

	public Pawn(int row, int col, boolean isWhite, GamePanel panel){
		super(row, col, isWhite, panel);
		type = PieceType.PAWN;
		image = panel.setImg(type, isWhite);				
	}

	@Override
	public ArrayList<Move> getMoves() {

		int startPosition = (!this.isWhite) ? 1 : 6;
		int direction = (!this.isWhite) ? 1 : -1;

		if(isHittingPiece((row + direction), col) == null) {
			if(row == startPosition) {
				if(addMove(row + direction, col) && isHittingPiece(row + (2 * direction), col) == null)
					addMove(row + (2 * direction), col);
			} else {
				addMove((row + direction), col);
			}
		}

		if(isHittingPiece((row + direction), col + 1) != null) {
			addMove((row + direction), (col + 1));
		}

		if(isHittingPiece((row + direction), col - 1) != null) {
			addMove((row + direction), (col - 1));
		}
		
		return moves;
	}

}
