import java.io.File
import kotlin.system.measureTimeMillis

fun main() {
    val contents = File("board2.txt").readText()

    val timeInMillis = measureTimeMillis {
        val board = Board.populate(contents).solve()
        board.dump()
    }

    println()
    println("${timeInMillis}ms")
}
