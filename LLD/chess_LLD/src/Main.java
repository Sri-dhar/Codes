public class Main {
    public static void main(String[] args) {
        System.out.println("Hello how are you");
    }
}

class Position{

}

abstract class Piece{
    Postion currentPosition;
    public void move(Position destination){
        if(isValid(currentPosition, destination)){

        }
    }

    boolean isValid(Postion Curr, Postion dest){
        Board temp = new Board();
        temp.makeMove();
        if(currentKingInCheck(temp)){
            return false;
        }
        else{
            return isValidMove();
        }
    }

    boolean currentKingInCheck(Board board){
        return false;
    }

    abstract void getAllPossibleMoves();
}

class Board{
    public void makeMove(Piece piece, Position destination){
        
    }
}

class Pawn{
    public void enpassant(){

    }

    bool hasMoved = false;

    public void promotion(){

    }
}

class King{
    public void castle(){
        //
    }
}

class Queen{

}

class Knight{

}

class Bishop{

}

class Rook{

}

