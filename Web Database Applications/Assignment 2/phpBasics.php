<!DOCTYPE html>
<html lang="en">
<head>
    <title>PHP Basics</title>

    <style>
        table{
            margin:auto;
            background-color: lavender;
            box-shadow: 2px 2px 10px darkslateblue;
            border-collapse: collapse;
            text-align: center;
        }

        th{
            padding: 15px;
            background-color: darkslateblue;
            color: white
        }

        td{
            border: 1px solid darkslateblue;  
            padding: 15px;
        }
    </style>
</head>
<body>
    <?php
        echo "<table>";
        echo "<tr><th>Numbers</th><th>Results</th></tr>";

        for($i = 1; $i <= 100; $i++){
            if($i%2 == 0){
                echo "<tr><td>$i</td><td>Even</td></tr>";
            }
            else{
                echo "<tr><td>$i</td><td>Odd</td></tr>";
            }
        }
        
        echo "</table>";
    ?>
</body>
</html>