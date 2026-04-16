package main;

import java.awt.event.*;

public class MouseHandler extends MouseAdapter {

	private int x;
	private int y;
	private Board board;

	MouseHandler(Board board) {
		this.board = board;
	}
	
	@Override
	public void mousePressed(MouseEvent e) {
		x = e.getX();
		y = e.getY();

		board.mouseControl(x, y);
	}
}
