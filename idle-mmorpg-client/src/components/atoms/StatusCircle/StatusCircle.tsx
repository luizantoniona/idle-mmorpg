import "./StatusCircle.css";

export type StatusType = "online" | "offline" | "error" | "loading" | "unknown";

interface StatusCircleProps {
    status: StatusType;
    size?: number;
}

export function StatusCircle({ status, size = 12 }: StatusCircleProps) {
    return (
        <span
            className={`status-circle ${status}`}
            style={{ width: size, height: size }}
            title={status}
        />
    );
}
