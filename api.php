<?php
require_once 'controller/ReasonsController.php';
require_once 'models/EnumStore.php';

$request = ($_GET['request']);
$parseRequest = explode('/', rtrim($request, '/'));
$controller = $parseRequest[0];
$request = $parseRequest[1];
switch ($controller)
{
    case EnumControllers::ReasonsController:
        $reasons = new ReasonsController($request);
        break;
    default:
        break;
}

$response = $reasons->processAPI();
$status = $response != null ? 200 : 404;
echo _response($response, $status);

function _response($data, $status = 200) {
    header("HTTP/1.1 " . $status . " " . _requestStatus($status));
    return json_encode($data);
}

function _requestStatus($code) {
    $status = array(
        200 => 'OK',
        404 => 'Not Found',
        405 => 'Method Not Allowed',
        500 => 'Internal Server Error',
    );
    return ($status[$code])?$status[$code]:$status[500];
}

?>