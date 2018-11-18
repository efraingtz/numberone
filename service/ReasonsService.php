<?
include $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/Response.php';
include $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/EnumStore.php';

class ReasonsService
{
    function GetDashboard()
    {
        $response = new PagedResult();
        $response->Data = [1,2,3];
        $response->Success = true;
        $response->Message = Constanst::DataSuccess;
        $response->Total = 10;
        return $response;
    }
}

?>