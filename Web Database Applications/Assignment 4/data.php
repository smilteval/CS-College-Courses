<?php
include_once "not_public/dbconnect.inc.php";
?>

<?php ////////////////////////////////////////////////////////////// Part 1

$amount = 75000;
$query1 = "SELECT * FROM CUSTOMER WHERE credit_limit <= ?";

$stmt = $conn->prepare($query1);
$stmt->bind_param("i", $amount);
$stmt->execute();
$result = $stmt->get_result();

if ($result->num_rows === 0) {
    exit(0);
}

$customers = $result->fetch_all(MYSQLI_ASSOC);

echo "<table border=1>
        <tr>
            <th>CUSTOMER_NUM</th>
            <th>CUSTOMER_NAME</th>
            <th>STREET</th>
            <th>CITY</th>
            <th>STATE</th>
            <th>ZIP</th>
            <th>BALANCE</th>
            <th>CREDIT_LIMIT</th>
            <th>REP_NUM</th>
        </tr>";

foreach ($customers as $customer) {
    echo "<tr>";
    foreach ($customer as $key => $value) {
        echo "<td>" . $value . "</td>";
    }
    echo "</tr>";
}
echo "</table>";

?>

<?php ////////////////////////////////////////////////////////////// Part 2

echo "<br><br>";

$query2 = "SELECT DISTINCT part_num FROM PART";

$stmt2 = $conn->prepare($query2);
$stmt2->execute();
$result2 = $stmt2->get_result();

if ($result2->num_rows === 0) {
    exit(0);
}

$parts = $result2->fetch_all(MYSQLI_ASSOC);

?>

<form method="POST">
    Parts:
    <select name="part">
        <option disabled selected>Select a part</option>
        <?php //dropdown menu
        foreach ($parts as $part) {
            foreach ($part as $key => $value) {
                echo "<option value='" . $value . "'>" . $value . "</option>";
            }
        }
        ?>
    </select>
    <button type="submit" name="submit">Get Info</button>
</form>

<?php // handle form submission

if (isset($_POST["submit"])) {

    $name = $_POST["part"];
    $query3 = "SELECT * FROM PART WHERE part_num = ?";

    $stmt3 = $conn->prepare($query3);
    $stmt3->bind_param("s", $name);
    $stmt3->execute();
    $result3 = $stmt3->get_result();

    if ($result3->num_rows === 0) {
        exit(0);
    }

    $partInfo = $result3->fetch_all(MYSQLI_ASSOC);

    echo "<table border=1>
            <tr>
                <th>PART_NUM</th>
                <th>DESCRIPTION</th>
                <th>ON_HAND</th>
                <th>CLASS</th>
                <th>WAREHOUSE</th>
                <th>PRICE</th>
            </tr>";

    foreach ($partInfo as $info) {
        echo "<tr>";
        foreach ($info as $key => $value) {
            echo "<td>" . $value . "</td>";
        }
        echo "</tr>";
    }

    echo "</table>";
}

?>