import java.io.File

fun main() {
    val contents = File("board2.txt").readText()

    val board = Board.populate(contents).solve()

    board.dump()
}
