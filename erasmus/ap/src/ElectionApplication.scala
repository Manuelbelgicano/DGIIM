object ElectionApplication {
    // Main menu string
    private val main_menu =
        "-------------------------------[ MAIN MENU ]-------------------------------\n" +
            "Choose an option:\n" +
            "\t0. Exit the application\n" +
            "\t1. Get all the election values.\n" +
            "\t2. Get the total number of votes of all states/districts.\n" +
            "\t3. Get the average votes per party of all states/districts.\n" +
            "\t4. Get the winning party and their % of votes of all states/districts.\n" +
            "\t5. Get the list of parties with their electoral votes won.\n" +
            "\t6. Get the total number of votes and % of votes of a specific party.\n" +
            "---------------------------------------------------------------------------\n" +
            "Your option: "

    // --------------------------------------------------------------------------------------
    // Main
    def main(args: Array[String]): Unit = {
        val handleAnalysis = analysisHandler(setData(scala.io.StdIn.readLine("Enter a file with elections results: ")))
        while (true) {
            println(main_menu)
            isOption(scala.io.StdIn.readLine()) match {
                case Some(opt: Int) => handleAnalysis(opt)
                case None => println("ERROR: Not a valid option. Choose again...")
            }
        }
    }

    // --------------------------------------------------------------------------------------
    // Analyses handlers
    // Creates the handler of a specific dataset
    private def analysisHandler(data: Map[String, List[(String, Int)]]) = (i: Int) => {
        i match {
            case 0 => scala.sys.exit()
            case 1 => electionValues(data)
            case 2 => totalNumberVotes(data)
            case 3 => averageVotes(data)
            case 4 => winningParty(data)
            case 5 => electoralVotes(data)
            case 6 => partyVotes(scala.io.StdIn.readLine("Choose a party: "), data)
        }
    }
    // Get all the election values (Analysis 1)
    def electionValues(data: Map[String, List[(String, Int)]]): Unit = printElectionInfo(data)
    // Get the total number of votes (Analysis 2)
    def totalNumberVotes(data: Map[String, List[(String, Int)]]): Unit = printTotalVotes(votesMap(data))
    // Get the average votes (Analysis 3)
    def averageVotes(data: Map[String, List[(String, Int)]]): Unit = printAverageVotes(averageVotesMap(data))
    // Get winning party (Analysis 4)
    def winningParty(data: Map[String, List[(String, Int)]]): Unit = printWinners(winnerMap(data))
    // Get all parties (Analysis 5)
    def electoralVotes(data: Map[String, List[(String, Int)]]): Unit = printElectoralVotes(electoralVotesList(data))
    // Get number of votes of party (Analysis 6)
    def partyVotes(party: String, data: Map[String, List[(String, Int)]]): Unit = printPartyVotes(partyVotes(data, party))

    // --------------------------------------------------------------------------------------
    // Print functions
    // Prints the election info
    def printElectionInfo(data: Map[String, List[(String, Int)]]): Unit = {
        // Creates the string with the info of a state
        def stateInfo(data: List[(String, Int)]): String = {
            data.foldLeft("") {
                (x, y) => x + "\n\t" + "The " + y._1 + " party had " + y._2 + " votes."
            }
        }

        val printData = data.map(x => (separateName(x._1)._1, stateInfo(x._2)))
        for (state <- printData) yield println(state._1 + " election info:" + state._2)
    }
    // Prints the total votes of each state
    def printTotalVotes(data: Map[String, Int]): Unit = {
        for (state <- data) yield println(separateName(state._1)._1 + " had a total of " + state._2 + " votes.")
    }
    // Prints the average votes of each state
    def printAverageVotes(data: Map[String, Float]): Unit = {
        for (state <- data) yield println(separateName(state._1)._1 + " had an average of " + state._2 + " votes per party.")
    }
    // Prints the winner with its % vote of each state
    def printWinners(data: Map[String, (String, Int)]): Unit = {
        for (state <- data) yield println("In " + separateName(state._1)._1 + " the " + state._2._1 + " party won with " + state._2._2 + "% of votes cast.")
    }
    // Prints the number of votes and % of a party
    def printPartyVotes(data: (String, Int, Int)): Unit = println("The " + data._1 + " party gained " + data._2 + " votes which is " + data._3 + "% of total votes cast.")
    // Prints the descending list of parties with electoral votes won
    def printElectoralVotes(data: List[(String, Int)]): Unit = {
        for (party <- data) yield println(party._1 + "(" + party._2 + ")")
    }

    // --------------------------------------------------------------------------------------
    // State calculations
    // Gets the total votes of a state.
    def stateVotes(data: List[(String, Int)]): Int = data.map(x => x._2).sum
    // Gets the average votes per party of a state.
    // The transformation Int->Double->Float is due to scala miscalculating some of the operations if floats are used
    def averageStateVotes(data: List[(String, Int)]): Float = (data.map(x => x._2).sum.toDouble / data.length).toFloat
    // Gets the winning party and its % vote.
    def stateWinner(data: List[(String, Int)]): (String, Int) = {
        val statePercent = percent(stateVotes(data))
        val winner = data.foldLeft(("", 0))((x, y) => if (x._2 >= y._2) x else y)
        (winner._1, statePercent(winner._2))
    }
    // Gets the votes of a party.
    def statePartyVotes(data: List[(String, Int)], party: String): Int = {
        if (data.map(x => x._1).exists(x => x.equals(party)))
            data.filter(x => x._1.equals(party)).head._2
        else
            0
    }
    // Gets the electoral votes won by a party.
    def stateElectoralVotes(data: (String, List[(String, Int)])): (String, Int) = {
        val winner = data._2.foldLeft(("", 0))((x, y) => if (x._2 >= y._2) x else y)._1
        (winner, separateName(data._1)._2)
    }

    // --------------------------------------------------------------------------------------
    // Global calculations
    // Calculates the total number of votes
    def totalVotes(data: Map[String, List[(String, Int)]]): Int = data.map(x => stateVotes(x._2)).sum
    // Creates a map containing the total number of votes of each state.
    def votesMap(data: Map[String, List[(String, Int)]]): Map[String, Int] = data.map(x => (x._1, stateVotes(x._2)))
    // Creates a map containing the average number of votes per party of each state.
    def averageVotesMap(data: Map[String, List[(String, Int)]]): Map[String, Float] = data.map(x => (x._1, averageStateVotes(x._2)))
    // Creates a map containing the winner and % votes of each state.
    def winnerMap(data: Map[String, List[(String, Int)]]): Map[String, (String, Int)] = data.map(x => (x._1, stateWinner(x._2)))
    // For a specific party, gets the total and % votes.
    def partyVotes(data: Map[String, List[(String, Int)]], party: String): (String, Int, Int) = {
        val electionPercent = percent(totalVotes(data))
        val votes = data.map(x => statePartyVotes(x._2, party)).sum
        (party, votes, electionPercent(votes))
    }
    // Creates the map of the electoral votes of each party
    def electoralVotesList(data: Map[String, List[(String, Int)]]): List[(String, Int)] = {
        val stateWinners = data.iterator.flatMap(x => List(stateElectoralVotes(x))).toList
        val parties = data.flatMap(x => x._2).flatMap(x => List(x._1)).toSet

        // Gets all the electoral votes of a party
        def totalElectoralVotes(data: List[(String, Int)], party: String): Int = data.filter(x => x._1.equals(party)).foldLeft(0)((y, z) => y + z._2)
        // Orders the results in a descending order
        (for (party <- parties) yield (party, totalElectoralVotes(stateWinners, party))).toList.sortWith((x, y) => x._2 > y._2)
    }

    // --------------------------------------------------------------------------------------
    // Auxiliary functions
    // Tests if the input is an option of the menu
    def isOption(input: String): Option[Int] = {
        if (input.matches("[0123456]"))
            Some(input.toInt)
        else
            None
    }
    // Creates a function to calculate the % of something
    private def percent(total: Int) = (n: Int) => {
        ((n.toFloat / total) * 100).round
    }
    // Separates the state string into the name and the electoral votes. Transforms String -> (String,Int)
    def separateName(stateName: String): (String, Int) = {
        val stateNameSplit = stateName.split("[()]")
        (stateNameSplit(0).trim, stateNameSplit(1).toInt)
    }
    // Gets the test data
    def setData(filename: String): Map[String, List[(String, Int)]] = {
        val bufferedFile = scala.io.Source.fromFile("./data/" + filename)
        val lines = bufferedFile.getLines.toList.map(x => x.split("[,]").toList).map(y => (y.head, y.takeRight(y.length - 1))).toMap
        // Separates the results of a state
        def separateResults(lines: List[String]): List[(String, Int)] = {
            // Transforms the string <Party>:<Votes> into a tuple
            def toTuple(data: String): (String, Int) = {
                val res = data.split("[:]")
                (res.head, res.last.toInt)
            }

            lines.map(x => toTuple(x))
        }

        bufferedFile.close
        lines.map(x => (x._1, separateResults(x._2)))
    }
}