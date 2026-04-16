package main;

import java.util.ArrayList;

import pieces.*;

public class Board {

	static boolean isWhite = Config.isWhite;
	public static ArrayList<Piece> pieces;
	public static ArrayList<Move> moves;
	public static Piece activePiece;
	public static boolean gameOver;
	GamePanel panel;

	Board(GamePanel panel) {
		pieces = new ArrayList<>();
		moves = new ArrayList<>();
		this.panel = panel;
		
		initializePieces(true);
		initializePieces(false);

		// //testing
		// pieces.add(new King(6, 6, true));
		// pieces.add(new King(6, 7, false));
	}

	public void initializePieces(boolean isWhite) {
		int topRow, bottomRow;
		
		if(isWhite) {
			topRow = 7;
			bottomRow = 6;
		} else {
			topRow = 0;
			bottomRow = 1;
		}

		pieces.add(new King(topRow, 4, isWhite, panel));
		pieces.add(new Queen(topRow, 3, isWhite, panel));

		pieces.add(new Bishop(topRow, 2, isWhite, panel));
		pieces.add(new Bishop(topRow, 5, isWhite, panel));

		pieces.add(new Knight(topRow, 1, isWhite, panel));
		pieces.add(new Knight(topRow, 6, isWhite, panel));

		pieces.add(new Rook(topRow, 0, isWhite, panel));
		pieces.add(new Rook(topRow, 7, isWhite, panel));

		for(int i = 0; i < 8; i++) 
			pieces.add(new Pawn(bottomRow, i, isWhite, panel));
	}

	public void changePlayer() {
		isWhite = !isWhite;
		activePiece = null;
		
		panel.flipBoard();
	}

	public void mouseControl(int x, int y) {
		if(activePiece == null) {
			for(Piece piece : pieces) {
				if(piece.isActive(x, y, isWhite)) {			
					activePiece = piece;
					moves = activePiece.getMoves();
					break;			
				}
			}
		} else {
			boolean moved = activePiece.makeMove(x, y);
			if(moved) {
				if(moves != null)
					moves.clear();
				if(gameOver) {
					 String winner = isWhite ? "White" : "Black"; 

					if(panel.rematch(winner)) {
						gameOver = false;
						pieces.clear();

						initializePieces(isWhite);
						initializePieces(!isWhite);
					} else {
						System.exit(0);
					}
				}
				changePlayer();
			}
		}
		panel.repaint();
	}
}
