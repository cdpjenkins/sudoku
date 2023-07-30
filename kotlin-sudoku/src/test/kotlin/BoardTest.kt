import io.kotest.matchers.shouldBe
import org.junit.jupiter.api.Test

class BoardTest {
    @Test
    fun `can parse and print a board`() {
        val board = Board.parse(BOARD1)

        board.dumpToString() shouldBe BOARD1
    }
}

val BOARD1 = """
            53__7____
            6__195___
            _98____6_
            8___6___3
            4__8_3__1
            7___2___6
            _6____28_
            ___419__5
            ____8__79
        """.trimIndent()