package main;

import javax.sound.sampled.*;
import java.net.URL;

public class Sounds {

	private static Clip[] clip = new Clip[3];
	private static URL[] soundURL = new URL[3];

	public Sounds() {
		soundURL[0] = getClass().getResource("/main/res/SF/move.wav");
		soundURL[1] = getClass().getResource("/main/res/SF/capture.wav");
		soundURL[2] = getClass().getResource("/main/res/SF/invalidmove.wav");

		for(int i = 0; i < 3; i++) {
			try(AudioInputStream audioStream = AudioSystem.getAudioInputStream(soundURL[i])) {
				clip[i] = AudioSystem.getClip();
				clip[i].open(audioStream);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	public static void playSE(int index) {
		if(!Config.soundOn) {
			return;
		}

		if(clip[index].isRunning()) {
			clip[index].stop();
		}

		clip[index].setFramePosition(0);
		clip[index].start();
	}
}
