package main;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;

import pieces.*;

public class GamePanel extends JPanel {

	public static final int BOARD_SIZE = Config.boardSize;
	public static final int BOX_SIZE = BOARD_SIZE / 8;
	public final int spriteSize = 400;
	private static BufferedImage whiteSheet = main.Config.whiteSheet;
	private static BufferedImage blackSheet = main.Config.blackSheet;
	public boolean isFlipped = !Config.isWhite;
	public final Color BLACK = Config.black;
	public final Color WHITE = Config.white;
	public final Color ACTIVECOLOR = Config.active;
	public final Color GREEN = Config.path;
	public final Color RED = Config.enemy;
	public final Color GRAY = Config.ally;
	public static Sounds sounds;
	public Board board;

	GamePanel() {
		this.setPreferredSize(new Dimension(BOARD_SIZE, BOARD_SIZE));
		board = new Board(this);
		this.addMouseListener(new MouseHandler(board));

		sounds = new Sounds();
	}

	public boolean isFlipped() {
		return isFlipped;
	}

	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2D = (Graphics2D) g;

		if(isFlipped) {
			g2D.translate(BOARD_SIZE, BOARD_SIZE);
			g2D.rotate(Math.toRadians(180));
		}

		drawBoard(g2D);

		if(Board.moves != null)
			drawMoves(g2D);

		for(Piece piece : Board.pieces)
			drawPiece(g2D, piece);

		if(Board.activePiece != null) {
			g2D.setPaint(ACTIVECOLOR);
			g2D.fillRect(Board.activePiece.getX(), Board.activePiece.getY(), BOX_SIZE, BOX_SIZE);
			drawPiece(g2D, Board.activePiece);
		}
	}

	private void drawBoard(Graphics2D g2D) {
		boolean isWhiteTile = !isFlipped;
	
		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				if(isWhiteTile) {
					g2D.setPaint(WHITE);
					g2D.fillRect(i * BOX_SIZE, j * BOX_SIZE, BOX_SIZE, BOX_SIZE);
					// g2D.setPaint(BLACK);//dev only
					// g2D.drawString(""+j+i, i * BOX_SIZE, j * BOX_SIZE + 10);//dev only
					isWhiteTile = false;
				} else {
					g2D.setPaint(BLACK);
					g2D.fillRect(i * BOX_SIZE, j * BOX_SIZE, BOX_SIZE, BOX_SIZE);
					// g2D.setPaint(WHITE);//dev only
					// g2D.drawString((""+j+i), i * BOX_SIZE, j * BOX_SIZE + 10);//dev only
					isWhiteTile = true;
				}								
			}
			isWhiteTile =!isWhiteTile;
		}	
	}

	public void drawPiece(Graphics2D g2D, Piece piece) {
		if(isFlipped){
			g2D.drawImage(piece.getImage(),
						  piece.getX(), piece.getY() + BOX_SIZE,
						  piece.getX() + BOX_SIZE, piece.getY(),
						  0, 0,
						  piece.getImage().getWidth(null), piece.getImage().getHeight(null), null);
		 //destination co-ordinates(start and end)y axis swapped for flipping, source co-ordinates(start and end)
		} else {
			g2D.drawImage(piece.getImage(), piece.getX(), piece.getY(), BOX_SIZE, BOX_SIZE, null);
		}
	}

	public BufferedImage setImg(PieceType type, boolean isWhite) {
		BufferedImage image;
		int spritePos = 0;
		switch (type) {
			case KING:   spritePos = 0; break;
			case QUEEN:  spritePos = 1; break;
			case BISHOP: spritePos = 2; break;
			case KNIGHT: spritePos = 3; break;
			case ROOK:   spritePos = 4; break;
			case PAWN:   spritePos = 5; break;
		}

		int spriteLoc = spritePos * spriteSize;
		
		if(isWhite) {
			image = whiteSheet.getSubimage(spriteLoc, 0, spriteSize, spriteSize);
		} else {
			image = blackSheet.getSubimage(spriteLoc, 0, spriteSize, spriteSize);
		}
		
		return image;
	}

	public void flipBoard() {
		if(Config.flippingOn) {
			isFlipped = !isFlipped;
		}
	}

	public void drawMoves(Graphics2D g2D) {
		for(Move move : Board.moves) {
			if(move.isEmpty)
				g2D.setPaint(GREEN);
			else if(move.isEnemy)
				g2D.setPaint(RED);
			else 
				g2D.setPaint(GRAY);
			g2D.fillRect(move.getX(), move.getY(), BOX_SIZE, BOX_SIZE);
		}
	}

    public boolean rematch(String winner) {
        int choice = JOptionPane.showConfirmDialog(null, winner + " won! do you wanna play again", 
        "Game Over", JOptionPane.YES_NO_OPTION, JOptionPane.INFORMATION_MESSAGE);

        if(choice == JOptionPane.YES_OPTION) { 
            return true;
        }

        return false;
    }
}
