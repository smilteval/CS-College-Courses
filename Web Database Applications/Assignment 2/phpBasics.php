<!DOCTYPE html>
<html lang="en">
<head>
    <title>PHP Basics</title>
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