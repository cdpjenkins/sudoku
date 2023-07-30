import java.io.File

fun main(args: Array<String>) {
    println("Hello World!")

    val contents = File("board1.txt").readLines()

    println(contents)

    val cells =
        contents.withIndex().flatMap { (y, line) ->
            line.withIndex().map { (x, ch) ->
                Position(x, y) to Cell.parse(ch)
            }
        }.toMap()

    println(cells   )
}

data class Cell(val possibilities: Set<Int>) {
    companion object {
        fun parse(ch: Char) = Cell(if (ch.isDigit()) setOf(ch.code) else emptySet())
    }
}

data class Position(val x: Int, val y:Int)

