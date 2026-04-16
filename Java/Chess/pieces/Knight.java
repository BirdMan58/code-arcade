package pieces;

import java.util.ArrayList;

import main.GamePanel;

public class Knight extends Piece {

	public Knight(int row, int col, boolean isWhite, GamePanel panel){
		super(row, col, isWhite, panel);
		type = PieceType.KNIGHT;
		image = panel.setImg(type, isWhite);	
	}

	@Override
	public ArrayList<Move> getMoves() {

		getKnightMoves(1, 1);
		getKnightMoves(-1, 1);
		getKnightMoves(1, -1);
		getKnightMoves(-1, -1);

		return moves;
	}

	public void getKnightMoves(int verticalDirection, int horizontalDirection) {
	
		addMove(row + (2 * verticalDirection), col + horizontalDirection);
		addMove(row + verticalDirection, col + (2 * horizontalDirection));
	}
}
