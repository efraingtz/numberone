<?

use Karriere\JsonDecoder\JsonDecoder;

include $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/BaseApi.php';
include $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/service/ReasonsService.php';
require_once $_SERVER['DOCUMENT_ROOT'].'/numberoneapi/models/entities/Reason.php';

class ReasonsController extends BaseApi
{
    protected $reasonsService;

    /**
     * ReasonsController constructor.
     * @param $request
     * @param $origin
     * @throws Exception
     */
    public function __construct($request) {
        parent::__construct($request,$this);
        $this->reasonsService = new ReasonsService();
    }


    protected function GetDashboard() {
        if ($this->method == 'GET') {
            $reason = new Reason();
            $reason->UserFromId = 1;
            $reason->UserToId =1;
            $reason->Priority = 1;
            $reason->Reason = "Reason ".$_GET["take"];
            $reason->Number = 3;
            $reason->ModifiedByUserId = 3;
            $reason->CreatedByUserId = 2;
            $reason->CreatedDate = $reason-> ModifiedDate = date('m/d/Y h:i:s a', time());
            //n$this->reasonsService->Cre ate($reason);
            return $this->reasonsService->GetDashboard();
        } else {

        }
    }

    protected function Create() {
        if ($this->method == 'PUT') {
            $inputJSON = file_get_contents('php://input');
            $jsonDecoder = new JsonDecoder();
            $reason = $jsonDecoder->decode($inputJSON, Reason::class);
            return $this->reasonsService->Create($reason);
        } else {

        }
    }
}

?>