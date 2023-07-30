import java.io.File

fun main() {
    val contents = File("board1.txt").readText()

    val board = Board.parse(contents)

    board.dump()
}
