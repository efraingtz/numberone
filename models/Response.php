<?

abstract class ResponseApi
{
    public $Data;
    public $Success = false;
    public $Message;
}

class SingleResult extends ResponseApi
{
   
}

class PagedResult extends ResponseApi
{
    public $Total;
}

?>