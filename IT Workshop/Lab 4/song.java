import java.util.*;

public class song {
    private static HashMap<Integer, song> songMap = new HashMap<>();
    private static int currentlyPlayingSongId = -1;
    private static int songCounter = 0;


    public static int getCurrentlyPlayingSongId() {
        return currentlyPlayingSongId;
    }

    public static void setCurrentlyPlayingSongId(int songId) {
        currentlyPlayingSongId = songId;
    }

    int songId;
    String songTitle;
    String artistName;
    String albumTitle;
    String genre;
    int durationInSecond;
    int playCount;

    public song(int duration) {
        durationInSecond = duration;
        this.playCount++;
    }

    public song() {
    }

    public int getSongId() {
        return songId;
    }

    public void setDetails() {
        Scanner scn = new Scanner(System.in);
        songCounter++;
        songId = songCounter;
        System.out.println("Enter the title of the song :");
        songTitle = scn.nextLine();
        System.out.println("Enter the name of the album  : ");
        albumTitle = scn.nextLine();
        System.out.println("Enter the song's genre : ");
        genre = scn.nextLine();
        System.out.println("Enter the duration of the song in seconds : ");
        durationInSecond = scn.nextInt();
        songMap.put(songId, this);
    }

    public void getDetails(int id) {
        if (songMap.containsKey(id)) {
            song currentSong = songMap.get(id);
            System.out.println("Song ID: " + currentSong.songId);
            System.out.println("Title: " + currentSong.songTitle);
            System.out.println("Album: " + currentSong.albumTitle);
            System.out.println("Genre: " + currentSong.genre);
            System.out.println("Duration (seconds): " + currentSong.durationInSecond);
            System.out.println("Play count: "+currentSong.playCount);
        } else {
            System.out.println("Song with ID " + id + " not found.");
        }
    }

    public static void geteverything() {
        for (Map.Entry<Integer, song> entry : songMap.entrySet()) {
            int songId = entry.getKey();
            song currentSong = entry.getValue();

            System.out.println("Song ID: " + songId);
            System.out.println("Title: " + currentSong.songTitle);
            System.out.println("Album: " + currentSong.albumTitle);
            System.out.println("Genre: " + currentSong.genre);
            System.out.println("Duration (seconds): " + currentSong.durationInSecond);
            System.out.println("Play count: "+currentSong.playCount);
            System.out.println();
        }
    }

    public void playSong() {
        Scanner scn = new Scanner(System.in);
        System.out.println("Enter the ID of the song you want to play:");
        int songId = scn.nextInt();

        if (songMap.containsKey(songId)) {
            setCurrentlyPlayingSongId(songId);
            song currentSong = songMap.get(songId);
            System.out.println("Playing song with ID " + songId);
            currentSong.incrementPlayCount();
        } else {
            System.out.println("Song with ID " + songId + " not found.");
        }
    }

    public void incrementPlayCount() {
        playCount++;
    }

    public song getSong(int index) {
        if (index >= 0 && index < songMap.size()) {
            return songMap.get(index + 1);
        } else {
            return null;
        }
    }
}

class Playlist {
    private List<song> songs;

    public Playlist() {
        songs = new ArrayList<>();
    }

    public void addSong(song song) {
        songs.add(song);
    }

    public void removeSong(int index) {
        if (index >= 0 && index < songs.size()) {
            songs.remove(index);
        }
    }

    public void listPlaylist() {
        System.out.println("Playlist:");
        for (int i = 0; i < songs.size(); i++) {
            song currentSong = songs.get(i);
            System.out.println((i + 1) + ". " + currentSong.songTitle);
        }
    }
}
