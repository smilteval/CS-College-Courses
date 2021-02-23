<!DOCTYPE html>
<html lang="en">
    <head>
        <title>PHP Arrays</title>

        <style>
        body {
            margin: 50px 100px 50px 100px;
        }

        table {
            background-color: lavender;
            box-shadow: 2px 2px 10px darkslateblue;
            border-collapse: collapse;
            text-align: center;
        }

        th {
            padding: 15px;
            background-color: darkslateblue;
            color: white
        }

        td {
            border: 1px solid darkslateblue;
            padding: 15px;
        }
        </style>

    </head>

    <body>
        <?php
            //-----------------------Part 1----------------------------
            
            echo "<h2>Original array of fruits</h2>";

            //Initialize an associative array of fruits
            $fruits = array(
                array("name" => "Apple", "calories"=> 95),
                array("name" => "Banana", "calories"=> 105),
                array("name" => "Orange", "calories"=> 45),
                array("name" => "Watermelon", "calories"=> 85),
                array("name" => "Kiwi", "calories"=> 42)
            );

            //Display the fruit array in a table format

            echo "<table>";
            echo "<tr><th>Fruit</th><th>Calories</th></tr>";

            foreach($fruits as $fruit){
                echo "<tr><td>$fruit[name]</td><td>$fruit[calories]</td></tr>";
            }

            echo "</table>";

            //-----------------------Part 2----------------------------

            //Copy the original fruit array and sort it using arsort()

            $reverseSortedFruits = $fruits; 
            arsort($reverseSortedFruits);

            //Description of what arsort() does

            echo "<h2><br>Arsort() </h2>";
            echo "<h4>This function sorts an array in reverse order such that array indices maintain their correlation with the array elements they are associated with.<br>This is used mainly when sorting associative arrays where the actual element order is significant.</h4>";

            //Display the sorted fruit array in a table format

            echo "<table>";
            echo "<tr><th>Fruit</th><th>Calories</th></tr>";

            foreach($reverseSortedFruits as $fruit){
                echo "<tr><td>$fruit[name]</td><td>$fruit[calories]</td></tr>";
            }

            echo "</table>";

            //-----------------------Part 3----------------------------

            //Copy the original fruit array and sort it by key in descending order

            $reverseByKeySortedFruits = $fruits; 
            krsort($reverseByKeySortedFruits);

            //Description of what arsort does

            echo "<h2><br>Krsort() </h2>";
            echo "<h4>This function sorts an array by key in reverse order, maintaining key to data correlations. </h4>";

            //Display the sorted fruit array in a table format

            echo "<table>";
            echo "<tr><th>Fruit</th><th>Calories</th></tr>";

            foreach($reverseByKeySortedFruits as $fruit){
                echo "<tr><td>$fruit[name]</td><td>$fruit[calories]</td></tr>";
            }

            echo "</table>";

            //-----------------------Part 4----------------------------

            //Calculate the total of calories from all fruits
            
            $totalCal = 0;

            foreach($fruits as $fruit){
                $totalCal += "$fruit[calories]";
            }

            //Print out the total of calories from all fruits
            
            echo "<h4><br>Total of calories from all 5 fruits: <u>$totalCal</u></h4>";
        
            //-----------------------Part 5----------------------------
        
            echo "<h2><br>Original array of users</h2>";

            $users = array(
                1 => array("user1" => "password1"),
                2 => array("user2" => "password2"),
                "3" => array("user3" => "password3"),
                array("user4" => "password4"),
            );

            //Explanation of the users array structure

            echo "<h4>This users array is a multi-dimensional associative array which means that the array itself contains other arrays.<br>In this case index numbers serve as keys while usernames with passwords are key value pairs.</h4>";

            //Display the user array in table format

            echo "<table>";
            echo "<tr><th>Username</th><th>Password</th></tr>";

            foreach($users as $index => $info){
                foreach ($info as $username => $password){
                    echo "<tr><td>$username</td><td>$password</td></tr>";
                }
            }
        ?>
    </body>
</html>