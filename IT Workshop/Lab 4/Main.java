import java.util.*;

public class Main {
    public static void main(String[] args) {
        int choice = 0;
        Scanner scn = new Scanner(System.in);
        song songg = new song();
        Playlist playlist = new Playlist();

        while (true) {
            System.out.println("Enter 1 to Set Details");
            System.out.println("Enter 2 to Get Details");
            System.out.println("Enter 3 to Play a song");
            System.out.println("Enter 4 to Add songs to a playlist");
            System.out.println("Enter 5 to Remove a song from a playlist");
            System.out.println("Enter 6 to Get details of every song ever entered");
            System.out.println("Enter 7 to List playlist");
            System.out.println("Enter 8 to Check currently playing song");
            System.out.println("Enter 9 to EXIT");
            choice = scn.nextInt();
            scn.nextLine();

            switch (choice) {
                case 1: 
                    song newSong = new song();
                    newSong.setDetails();
                    playlist.addSong(newSong);
                    break;
                case 2:
                    System.out.println("Enter the ID number: ");
                    int id = scn.nextInt();
                    songg.getDetails(id);
                    System.out.println();
                    break;
                case 3:
                    songg.playSong();
                    break;
                case 4:
                    System.out.println("Enter the ID of the song to add to the playlist:");
                    int indexToAdd = scn.nextInt();
                    song songToAdd = songg.getSong(indexToAdd - 1);
                    if (songToAdd != null) {
                        playlist.addSong(songToAdd);
                        System.out.println("Song added to the playlist.");
                    } else {
                        System.out.println("Invalid index. Song not added to the playlist.");
                    }
                    break;

                case 5:
                    System.out.println("Enter the index to remove song from :");
                    int indexToRemove = scn.nextInt();
                    playlist.removeSong(indexToRemove);
                    break;
                case 6:
                    song.geteverything();
                    break;
                case 7:
                    playlist.listPlaylist();
                    break;
                case 8:
                    int playingSongId = song.getCurrentlyPlayingSongId();
                    if (playingSongId == -1) {
                        System.out.println("No song is currently playing.");
                    } else {
                        System.out.println("Currently playing song ID: " + playingSongId);
                    }
                    break;
                case 9:
                    System.out.println("Exiting program.");
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice. Please enter a valid option.");
            }
        }
    }
}
